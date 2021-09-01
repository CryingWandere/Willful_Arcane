#pragma once

#include "resource_holder.hpp"
#include "resource_identify.hpp"

#include "quote_identify.hpp"

#include "scene_node.hpp"
#include "sprite_node.hpp"

#include "command_queue.hpp"
#include "command.hpp"

#include "hero.hpp"
#include "enemy.hpp"
#include "npc.hpp"

#include "dialogue.hpp"

#include < SFML/System/NonCopyable.hpp >
#include < SFML/Graphics/View.hpp >
#include < SFML/Graphics/Texture.hpp >

#include < array >

//Forward declaration
namespace sf
{
	class RenderWindow;
}

class World : private sf::NonCopyable
{
public:
	enum DialogStatus
	{
		Forward,
		Jump,
		End,

		AllPossible
	};

public:
	explicit World( sf::RenderWindow& window, FontHolder& fonts );

	void update( sf::Time delta );
	void draw();

	CommandQueue& getCommandQueue();

	void setStartQuote( Quotes::ID startQuote );
	Quotes::ID getStartQuote() const;

	void setConvIsRepeated( bool convIsRepeated );
	bool getConvIsRepeated() const;

private:
	void loadTextures();
	
	void correctVelocity();
	void correctEntityPosition();

	void handleCollisions();

	void buildScene();
	void addEnemies();
	void addEnemy( Enemy::Type type, float relX, float relY );
	void spawnEnemies();
	void guideEnemies();

	bool matchesCategories( SceneNode::Pair& colliders, Category::Type type1, Category::Type type2 );

private:
	enum Layer
	{
		LAYER_NULL,

		Background,
		MainLayer,

		LAYER_LIMIT
	};

	struct Spawner
	{
		Spawner( Enemy::Type type, float x, float y )
			:	type( type )
			,	x( x )
			,	y( y )
		{
		}

		Enemy::Type type;
		float x;
		float y;
	};

private:
	sf::RenderWindow& m_window;
	sf::View m_view;

	TextureHolder m_textures;
	FontHolder& m_fonts;

	SceneNode m_sceneGraph;
	std::array< SceneNode*, LAYER_LIMIT > m_sceneLayers;

	CommandQueue m_commandQueue;

	sf::FloatRect m_worldBorders;
	sf::Vector2f m_spawnPoint;

	Hero* m_hero;

	std::vector< Spawner > m_enemySpawners;
	std::vector< Enemy* > m_activeEnemies;

	bool m_b_convIsRepeated;

	Quotes::ID m_startQuote;
};