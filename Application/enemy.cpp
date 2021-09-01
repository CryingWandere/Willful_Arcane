#include "enemy.hpp"

#include "data_storage.hpp"
#include "command_queue.hpp"
#include "resource_holder.hpp"
#include "utilities.hpp"

#include < SFML/Graphics/RenderTarget.hpp >
#include < SFML/Graphics/RenderStates.hpp >

#include < cassert >

//global region
namespace
{
	const std::vector< EnemyData > Table = initializeEnemyData();
}

Enemy::Enemy( Type type, const TextureHolder& textures, const FontHolder& fonts )
	:	Entity( Table[ type ].hitpoints )
	,	m_type( type )
	,	m_sprite( textures.get( Table[ type ].texture ) )
	,	m_travelledDistance( 0.f )
	,	m_directionIndex( 0 )
	,	m_healthDisplay( nullptr )
	,	m_targetDirection()
	,	m_attackCooldown( sf::Time::Zero )
	,	m_movementCooldown( sf::Time::Zero )
	,	m_stopCooldown( sf::Time::Zero )
	,	m_second( sf::Time::Zero )
	,	m_b_last( true )
	,	m_b_isMarkedForRemoval( false )
	,	m_b_isAttacking( false )
	,	m_attackCommand()
{
	m_attackCommand.category = Category::Scene;
	m_attackCommand.action = [ this, &textures ]( SceneNode& node, sf::Time )
	{
		createAttack( node, textures );
	};

	centerOrigin( m_sprite );

	std::unique_ptr< TextNode > healthDisplay( new TextNode( fonts, L"" ) );
	m_healthDisplay = healthDisplay.get();
	attachChild( std::move( healthDisplay ) );

	updateText();
}

void Enemy::guideTowards( sf::Vector2f position )
{
	assert( isGuided() );
	m_targetDirection = unitVector( position - getWorldPosition() );
}

bool Enemy::isGuided() const
{
	return m_type == BasicGuided;
}

void Enemy::drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const
{
	target.draw( m_sprite, states );
}

void Enemy::updateCurrent( sf::Time delta, CommandQueue& commands )
{
	if ( isDestroyed() )
	{
		m_b_isMarkedForRemoval = true;
		return;
	}

	updateEnemyDirection();

	if ( m_movementCooldown <= sf::Time::Zero and m_stopCooldown <= sf::Time::Zero )
	{
		updateMovementPattern( delta );
	}
	else if ( m_movementCooldown > sf::Time::Zero )
	{
		m_movementCooldown -= delta;
	}
	else if ( m_stopCooldown > sf::Time::Zero )
	{
		setVelocity( 0.1f, 0.1f );
		m_stopCooldown -= delta;
	}

	if ( m_second <= sf::Time::Zero )
	{
		if ( getRandomInt( 5 ) == 2 and m_movementCooldown <= sf::Time::Zero )
			m_movementCooldown = ( sf::milliseconds( 300 + getRandomInt( 700 ) ) );
		if ( getRandomInt( 9 ) == 2 and m_stopCooldown <= sf::Time::Zero )
			m_stopCooldown = ( sf::milliseconds ( 300 + getRandomInt( 1500 ) ) );

		m_second += sf::seconds( 1 );
	}
	else if ( m_second > sf::Time::Zero )
	{
		m_second -= delta;
	}

	Entity::updateCurrent( delta, commands );

	checkAttack( delta, commands );

	updateText();
}

void Enemy::updateMovementPattern( sf::Time delta )
{
	if ( isGuided() )
	{
		sf::Vector2f newVelocity = unitVector( 10000.f * delta.asSeconds() * m_targetDirection + getVelocity() );
		newVelocity *= getMaxSpeed();
		//float angle = std::atan2( newVelocity.y, newVelocity.x );

		setVelocity( newVelocity );
	}
	else
	{
		const std::vector< Direction >& directions = Table[ m_type ].directions;

		if ( !directions.empty() )
		{
			if ( m_travelledDistance > directions[ m_directionIndex ].distance )
			{
				m_directionIndex = ( m_directionIndex + 1 ) % directions.size();
				m_travelledDistance = 0.f;
			}

			float radians = toRadian( directions[ m_directionIndex ].angle + 90.f );
			float vx = getMaxSpeed() * std::cos( radians );
			float vy = getMaxSpeed() * std::sin( radians );

			setVelocity( vx, vy );

			m_travelledDistance += getMaxSpeed() * delta.asSeconds();
		}
	}
}

unsigned int Enemy::getCategory() const
{
	return Category::Enemy;
}

sf::FloatRect Enemy::getBoundingRect() const
{
	return getWorldTransform().transformRect( m_sprite.getGlobalBounds() );
}

bool Enemy::isMarkedForRemoval() const
{
	return m_b_isMarkedForRemoval;
}

float Enemy::getMaxSpeed() const
{
	return Table[ m_type ].speed;
}

void Enemy::attack()
{
	m_b_isAttacking = true;
}

void Enemy::checkAttack( sf::Time delta, CommandQueue& commands )
{
	attack();

	if ( m_b_isAttacking and m_attackCooldown <= sf::Time::Zero )
	{
		commands.add( m_attackCommand );

		m_attackCooldown += Table[ m_type ].attackCooldown;
		m_b_isAttacking = false;
	}
	else if ( m_attackCooldown > sf::Time::Zero )
	{
		m_attackCooldown -= delta;
		m_b_isAttacking = false;
	}
}

void Enemy::createAttack( SceneNode& node, const TextureHolder& textures ) const
{
	Weapon::Type type = Weapon::EnemySword;

	if ( !m_b_last )
		createWeapon( node, type, 0.5f, 0.0f, false, textures );
	else
		createWeapon( node, type, -0.5f, 0.0f, true, textures );
}

void Enemy::createWeapon( SceneNode& node, Weapon::Type type, float xOffset, float yOffset, bool invert, const TextureHolder& textures ) const
{
	std::unique_ptr< Weapon > weapon( new Weapon( type, textures ) );

	sf::Vector2f offset( xOffset * m_sprite.getGlobalBounds().width + xOffset * 14.f, yOffset * m_sprite.getGlobalBounds().height + 7.f );
	
	if ( invert )
	{
		weapon->setRotation( -180.f );
	}

	weapon->setPosition( getWorldPosition() + offset );
	node.attachChild( std::move( weapon ) );
}

void Enemy::updateEnemyDirection()
{
	if ( Table[ m_type ].b_hasRotateAnimation )
	{
		sf::IntRect textureRect;
		
		//Go left
		if ( getVelocity().x < 0.f )
		{
			textureRect = Table[ m_type ].textureRect;
			m_b_last = true;
		}
		//Go right
		else if ( getVelocity().x > 0.f )
		{
			textureRect = Table[ m_type ].mirroredTextureRect;
			m_b_last = false;
		}
		else if ( m_b_last )
			textureRect = Table[ m_type ].textureRect;
		else
			textureRect = Table[ m_type ].mirroredTextureRect;

		m_sprite.setTextureRect( textureRect );
	}
}

void Enemy::updateText()
{
	m_healthDisplay->setString( std::to_wstring( getHitpoints() ) + L" HP" );
	m_healthDisplay->setPosition( 0.f, -70.f );
	m_healthDisplay->setRotation( -getRotation() );
}