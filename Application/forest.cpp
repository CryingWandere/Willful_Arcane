#include "forest.hpp"

#include "text_node.hpp"

#include "SFML/Graphics/RenderWindow.hpp"

//Класс игрового мира для второй локации

Forest::Forest( sf::RenderWindow& window, FontHolder& fonts )
	:	m_window( window )
	,	m_view( window.getDefaultView() )
	,	m_fonts( fonts )
	,	m_textures()
	,	m_sceneGraph()
	,	m_sceneLayers()
	,	m_worldBorders( 0.f, 760.f, 3840.f, 2240.f )
	,	m_textureBorders( 0.f, 0.f, 3840.f, 3000.f )
	,	m_spawnPoint( 1200.f, 2100.f )
	,	m_hero( nullptr )
	,	m_timer( sf::milliseconds( 400 ) )
	,	m_hits( 0 )
{
	loadTextures();
	buildScene();

	m_view.setCenter( m_spawnPoint );
}

void Forest::update( sf::Time delta )
{
	m_view.setCenter( m_hero->getWorldPosition() );
	m_hero->setVelocity( 0.f, 0.f );

	while ( !m_commandQueue.isEmpty() )
		m_sceneGraph.onCommand( m_commandQueue.remove(), delta );

	correctVelocity();

	handleCollisions();

	m_sceneGraph.removeCorpses();
	spawnEnemies();
	guideEnemies();

	m_sceneGraph.update( delta, m_commandQueue );
	correctEntityPosition();


	if ( m_timer <= sf::Time::Zero )
	{
		destroyEntities();
		m_timer += sf::milliseconds( 400 );
	}
	else if ( m_timer > sf::Time::Zero )
	{
		m_timer -= delta;
	}
}

void Forest::draw()
{
	m_window.setView( m_view );
	m_window.draw( m_sceneGraph );
}

CommandQueue& Forest::getCommandQueue()
{
	return m_commandQueue;
}

bool Forest::hasAliveHero() const
{
	return !m_hero->isMarkedForRemoval();
}

bool Forest::hasHeroWon() const
{
	return m_hits >= 7 * 12;
}

void Forest::loadTextures()
{
	m_textures.load( Textures::Oleg, "Textures/heroes_bgs/warrior/warrior_default.png" );
		m_textures.load( Textures::Sword, "Textures/heroes_bgs/warrior/sword.png" );

	m_textures.load( Textures::UndeadOld, "Textures/enemies_bgs/undead_old.png" );

	//m_textures.load( Textures::PeasantGirl, "Textures/npcs_bgs/peasant_girl.png" );

	m_textures.load( Textures::Background02, "Textures/level_bgs/world02.png" );
	m_textures.load( Textures::Foreground01, "Textures/level_bgs/foreground_trees.png" );
}

void Forest::buildScene()
{
	for ( std::size_t cntr = 0; cntr < LAYER_LIMIT; cntr++ )
	{
		SceneNode::Pointer layer( new SceneNode );

		m_sceneLayers[ cntr ] = layer.get();

		m_sceneGraph.attachChild( std::move( layer ) );
	}

	sf::Texture& texture = m_textures.get( Textures::Background02 );
	sf::IntRect textureRect( m_textureBorders );

	std::unique_ptr< SpriteNode > backgroundSprite( new SpriteNode( texture, textureRect ) );
	backgroundSprite->setPosition( m_textureBorders.left, m_textureBorders.top );
	m_sceneLayers[ Background ]->attachChild( std::move( backgroundSprite ) );

	sf::Texture& texture_f = m_textures.get( Textures::Foreground01 );
	sf::IntRect textureRect_f( m_textureBorders );

	std::unique_ptr< SpriteNode > foregroundSprite( new SpriteNode( texture_f, textureRect_f ) );
	foregroundSprite->setPosition( m_textureBorders.left, m_textureBorders.top );
	m_sceneLayers[ Foreground ]->attachChild( std::move( foregroundSprite ) );

	std::unique_ptr< Hero > hero( new Hero( Hero::Warrior, m_textures, m_fonts ) );
	m_hero = hero.get();
	m_hero->setTextVisibility( true );
	m_hero->setAttack( true );
	m_hero->setPosition( m_spawnPoint );
	m_sceneLayers[ MainLayer ]->attachChild( std::move( hero ) );

	addEnemies();
}

void Forest::addEnemies()
{
	addEnemy( Enemy::BasicGuided, 800.f, 200.f );
	addEnemy( Enemy::BasicGuided, 1600.f, 300.f );
	addEnemy( Enemy::BasicGuided, 800.f, 3000.f );
	addEnemy( Enemy::BasicGuided, 0.f, 2000.f );
}

void Forest::addEnemy( Enemy::Type type, float relX, float relY )
{
	Spawner spawner( type, m_spawnPoint.x + relX, m_spawnPoint.y - relY );
	m_enemySpawners.push_back( spawner );
}

void Forest::spawnEnemies()
{
	while ( !m_enemySpawners.empty() )
	{
		Spawner spawner = m_enemySpawners.back();

		std::unique_ptr< Enemy > enemy( new Enemy( spawner.type, m_textures, m_fonts ) );
		enemy->setPosition( spawner.x, spawner.y );
		enemy->setVelocity( 1.f, 1.f );

		m_sceneLayers[ MainLayer ]->attachChild( std::move( enemy ) );

		m_enemySpawners.pop_back();
	}
}

void Forest::guideEnemies()
{
	Command enemyGuider;
	enemyGuider.category = Category::Enemy;
	enemyGuider.action = obtainedAction< Enemy >( [ this ] ( Enemy& enemy, sf::Time )
	{
		if ( !enemy.isGuided() )
			return;

		enemy.guideTowards( m_hero->getWorldPosition() );
	});

	m_commandQueue.add( enemyGuider );
}

void Forest::correctVelocity()
{
	sf::Vector2f velocity = m_hero->getVelocity();

	if ( velocity.x != 0.f && velocity.y != 0.f )
		m_hero->setVelocity( velocity / std::sqrt( 2.f ) );
}

void Forest::correctEntityPosition()
{
	const float xBorderDistance = 40.f;
	const float yBorderDistance = 55.f;

	sf::Vector2f worldPosition = m_hero->getWorldPosition();
	worldPosition.x = std::max( worldPosition.x, m_worldBorders.left + xBorderDistance );
	worldPosition.x = std::min( worldPosition.x, m_worldBorders.left + m_worldBorders.width - xBorderDistance );
	worldPosition.y = std::max( worldPosition.y, m_worldBorders.top + yBorderDistance );
	worldPosition.y = std::min( worldPosition.y, m_worldBorders.top + m_worldBorders.height - yBorderDistance );

	m_hero->setPosition( worldPosition );
}

bool Forest::matchesCategories( SceneNode::Pair& colliders, Category::Type type1, Category::Type type2 )
{
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

	if ( type1 & category1 && type2 & category2 )
	{
		return true;
	}
	else if ( type1 & category2 && type2 & category1 )
	{
		std::swap( colliders.first, colliders.second );
		return true;
	}
	else
		return false;
}

void Forest::handleCollisions()
{
	std::set< SceneNode::Pair > collisionPairs;
	m_sceneGraph.checkSceneCollision( m_sceneGraph, collisionPairs );

	for ( SceneNode::Pair pair : collisionPairs )
	{
		if ( matchesCategories( pair, Category::AlliedWeapon, Category::Enemy ) )
		{
			auto& weapon = static_cast< Weapon& >( *pair.first );
			auto& enemy = static_cast< Enemy& >( *pair.second );

			enemy.damage( weapon.getDamage() );
			weapon.destroy();

			m_hits++;
		}

		else if ( matchesCategories( pair, Category::EnemyWeapon, Category::Hero ) )
		{
			auto& weapon = static_cast< Weapon& >( *pair.first );
			auto& hero = static_cast< Hero& >( *pair.second );

			hero.damage( weapon.getDamage() );
			weapon.destroy();
		}
	}
}

void Forest::destroyEntities()
{
	Command command;
	command.category = Category::AlliedWeapon | Category::EnemyWeapon | Category::Enemy;
	command.action = obtainedAction< Entity >( [ this ] ( Entity& e, sf::Time )
	{
		if ( e.getCategory() == Category::AlliedWeapon or e.getCategory() == Category::EnemyWeapon )
		{
			e.destroy();
		}
	} );

	m_commandQueue.add( command );
}