#include "hero.hpp"

#include "bools.hpp"
#include "dialogue.hpp"

#include "data_storage.hpp"
#include "command_queue.hpp"
#include "resource_holder.hpp"
#include "utilities.hpp"

#include < SFML/Graphics/RenderTarget.hpp >
#include < SFML/Graphics/RenderStates.hpp >

//global region
namespace
{
	const std::vector< HeroData > Table = initializeHeroData();
}

Hero::Hero( Type type, const TextureHolder& textures, const FontHolder& fonts )
	:	Entity( Table[ type ].hitpoints )
	,	m_type( type )
	,	m_sprite( textures.get( Table[ type ].texture ) )
	,	m_healthDisplay( nullptr )
	,	m_attackCooldown( sf::Time::Zero )
	,	m_healCooldown( sf::Time::Zero )
	,	m_b_isTextVisible( true )
	,	m_b_isAttackRequired( false )
	,	m_b_last( true )
	,	m_b_isInteracting( false )
	,	m_b_isAttacking( false )
	,	m_b_isMarkedForRemoval( false )
	,	m_interactCommand()
	,	m_attackCommand()
{
	m_interactCommand.category = Category::Scene;
	m_interactCommand.action = [ this, &textures ]( SceneNode& node, sf::Time )
	{
		createInteraction();
	};

	m_attackCommand.category = Category::Scene;
	m_attackCommand.action = [ this, &textures ]( SceneNode& node, sf::Time )
	{
		createAttack( node, textures );
	};

	centerOrigin( m_sprite );

	std::unique_ptr< TextNode > healthDisplay( new TextNode( fonts, L"" ) );
	m_healthDisplay = healthDisplay.get();
	attachChild( std::move( healthDisplay ) );
}

void Hero::drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const
{
	target.draw( m_sprite, states );
}

void Hero::updateCurrent( sf::Time delta, CommandQueue& commands )
{
	if ( isDestroyed() )
	{
		m_b_isMarkedForRemoval = true;
		return;
	}

	updateHeroDirection();
	Entity::updateCurrent( delta, commands );

	checkInteraction( delta, commands );
	checkAttack( delta, commands );

	if ( m_b_isTextVisible )
		updateText();

	if ( getHitpoints() < Table[ m_type ].hitpoints and m_healCooldown <= sf::Time::Zero )
	{
		heal ( 1 );
		m_healCooldown += sf::milliseconds( 800 );
	}
	else if ( m_healCooldown > sf::Time::Zero )
	{
		m_healCooldown -= delta;
	}
}

unsigned int Hero::getCategory() const
{
	switch ( m_type )
	{
	case Warrior:
		return Category::Hero;

	default:
		return Category::Hero;
	}
}

sf::FloatRect Hero::getBoundingRect() const
{
	return getWorldTransform().transformRect( m_sprite.getGlobalBounds() );
}

bool Hero::isMarkedForRemoval() const
{
	return m_b_isMarkedForRemoval;
}

float Hero::getMaxSpeed() const
{
	return Table[ m_type ].speed;
}

void Hero::setTextVisibility( bool b_visible )
{
	m_b_isTextVisible = b_visible;
}

bool Hero::getTextVisibility() const
{
	return m_b_isTextVisible;
}

void Hero::setAttack( bool attack )
{
	m_b_isAttackRequired = attack;
}

bool Hero::getAttack() const
{
	return m_b_isAttackRequired;
}

void Hero::interact()
{
	m_b_isInteracting = true;
}

void Hero::checkInteraction( sf::Time delta, CommandQueue& commands )
{
	if ( m_b_isInteracting )
	{
		commands.add( m_interactCommand );
		m_b_isInteracting = false;
	}
}

void Hero::createInteraction() const
{
	Bools::Hero::setInteract( true );
}

void Hero::attack()
{
	if ( m_b_isAttackRequired )
		m_b_isAttacking = true;
}

void Hero::checkAttack( sf::Time delta, CommandQueue& commands )
{
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

void Hero::createAttack( SceneNode& node, const TextureHolder& textures ) const
{
	Weapon::Type type = Weapon::Sword;

	if ( !m_b_last )
		createWeapon( node, type, 0.5f, 0.0f, false, textures );
	else
		createWeapon( node, type, -0.5f, 0.0f, true, textures );
}

void Hero::createWeapon( SceneNode& node, Weapon::Type type, float xOffset, float yOffset, bool invert, const TextureHolder& textures ) const
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

void Hero::updateHeroDirection()
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

void Hero::updateText()
{
	m_healthDisplay->setString( std::to_wstring( getHitpoints() ) + L" HP" );
	m_healthDisplay->setPosition( 0.f, -70.f );
	m_healthDisplay->setRotation( -getRotation() );
}