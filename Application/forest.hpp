#pragma once

#include "resource_holder.hpp"
#include "resource_identify.hpp"

//#include "quote_identify.hpp"

#include "scene_node.hpp"
#include "sprite_node.hpp"

#include "command_queue.hpp"
#include "command.hpp"

#include "hero.hpp"
#include "enemy.hpp"
//#include "npc.hpp"

//#include "dialogue.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>

//Forward declaration
namespace sf
{
	class RenderWindow;
}

class Forest : private sf::NonCopyable
{
/*
public:
	enum DialogStatus
	{
		Forward,
		Jump,
		End,

		AllPossible
	};
*/
public:
	explicit Forest( sf::RenderWindow& window, FontHolder& fonts );

	void update( sf::Time delta );
	void draw();

	CommandQueue& getCommandQueue();

	bool hasAliveHero() const;
	bool hasHeroWon() const;

private:
	void loadTextures();
	
	void correctVelocity();
	void correctEntityPosition();

	void handleCollisions();
	void destroyEntities();

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
		Foreground,

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
	sf::FloatRect m_textureBorders;
	sf::Vector2f m_spawnPoint;

	Hero* m_hero;

	sf::Time m_timer;

	std::vector< Spawner > m_enemySpawners;
	std::vector< Enemy* > m_activeEnemies;

	int m_hits;
};
