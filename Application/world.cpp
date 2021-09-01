#include "world.hpp"

#include "bools.hpp"
#include "text_node.hpp"

#include "SFML/Graphics/RenderWindow.hpp"

World::World( sf::RenderWindow& window, FontHolder& fonts )
	:	m_window( window )
	,	m_view( window.getDefaultView() )
	,	m_fonts( fonts )
	,	m_textures()
	,	m_sceneGraph()
	,	m_sceneLayers()
	,	m_worldBorders( 0.f, 0.f, 3840.f, 2160.f )
	,	m_spawnPoint( 960.f, 540.f )
	,	m_hero( nullptr )
	,	m_b_convIsRepeated( false )
	,	m_startQuote( Quotes::conversation_D01_quote_PG_00 )
{
	loadTextures();
	buildScene();

	m_view.setCenter( m_spawnPoint );
}

void World::update( sf::Time delta )
{
	m_view.setCenter( m_hero->getWorldPosition() ); //!!
	m_hero->setVelocity( 0.f, 0.f );

	while ( !m_commandQueue.isEmpty() )
		m_sceneGraph.onCommand( m_commandQueue.remove(), delta );

	correctVelocity();

	handleCollisions();

	spawnEnemies();
	guideEnemies();

	m_sceneGraph.update( delta, m_commandQueue );
	correctEntityPosition();
}

void World::draw()
{
	m_window.setView( m_view );
	m_window.draw( m_sceneGraph );
}

CommandQueue& World::getCommandQueue()
{
	return m_commandQueue;
}

void World::loadTextures()
{
	m_textures.load( Textures::Oleg, "Textures/heroes_bgs/warrior/warrior_default.png" );

	m_textures.load( Textures::PeasantGirl, "Textures/npcs_bgs/peasant_girl.png" );

	m_textures.load( Textures::Background01, "Textures/level_bgs/world01.png" );
}

void World::buildScene()
{
	//Layers
	for ( std::size_t cntr = 0; cntr < LAYER_LIMIT; cntr++ )
	{
		SceneNode::Pointer layer( new SceneNode );

		m_sceneLayers[ cntr ] = layer.get();

		m_sceneGraph.attachChild( std::move( layer ) );
	}

	//Bg
	sf::Texture& texture = m_textures.get( Textures::Background01 );
	sf::IntRect textureRect( m_worldBorders );

	std::unique_ptr< SpriteNode > backgroundSprite( new SpriteNode( texture, textureRect ) );
	backgroundSprite->setPosition( m_worldBorders.left, m_worldBorders.top );
	m_sceneLayers[ Background ]->attachChild( std::move( backgroundSprite ) );

	//Hero
	std::unique_ptr< Hero > hero( new Hero( Hero::Warrior, m_textures, m_fonts ) );
	m_hero = hero.get();
	m_hero->setTextVisibility( false );
	m_hero->setPosition( m_spawnPoint );
	m_sceneLayers[ MainLayer ]->attachChild( std::move( hero ) );

	//PG
	std::unique_ptr< NPC > haymaker( new NPC( NPC::PeasantGirl, m_textures, m_fonts ) );
	haymaker->setPosition( 1920.f, 1080.f );
	//haymaker->setVelocity( 0.f, 0.f );
	m_sceneLayers[ MainLayer ]->attachChild( std::move( haymaker ) );

	addEnemies();
}

void World::addEnemies()
{
	addEnemy( Enemy::BasicGuided, 800.f, 200.f ); //temporarily
}

void World::addEnemy( Enemy::Type type, float relX, float relY )
{
	Spawner spawner( type, m_spawnPoint.x + relX, m_spawnPoint.y - relY );
	m_enemySpawners.push_back( spawner );
}

void World::spawnEnemies()
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

void World::guideEnemies()
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

void World::correctVelocity()
{
	sf::Vector2f velocity = m_hero->getVelocity();

	if ( velocity.x != 0.f && velocity.y != 0.f )
		m_hero->setVelocity( velocity / std::sqrt( 2.f ) );
}

void World::correctEntityPosition()
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

bool World::matchesCategories( SceneNode::Pair& colliders, Category::Type type1, Category::Type type2 )
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

void World::handleCollisions()
{
	std::set< SceneNode::Pair > collisionPairs;
	m_sceneGraph.checkSceneCollision( m_sceneGraph, collisionPairs );

	for ( SceneNode::Pair pair : collisionPairs )
	{
		if	( matchesCategories( pair, Category::Hero, Category::NPC ) && Bools::Hero::getInteract() )
			Dialogue::setConv( true );
	}
}

void World::setStartQuote( Quotes::ID startQuote )
{
	m_startQuote = startQuote;
}

Quotes::ID World::getStartQuote() const
{
	return m_startQuote;
}

void World::setConvIsRepeated( bool convIsRepeated )
{
	m_b_convIsRepeated = convIsRepeated;
}

bool World::getConvIsRepeated() const
{
	return m_b_convIsRepeated;
}
