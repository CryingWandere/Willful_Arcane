#pragma once

#include "category.hpp"

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <set>

//Forward declaration
struct Command;
class CommandQueue;

class SceneNode : public sf::Transformable, public sf::Drawable, public sf::NonCopyable
{
public:
	typedef std::unique_ptr< SceneNode > Pointer;

	typedef std::pair< SceneNode*, SceneNode* > Pair;

public:
	SceneNode();

	void attachChild( Pointer child );
	Pointer detachChild( const SceneNode& node );

	void update( sf::Time delta, CommandQueue& commands );

	sf::Vector2f getWorldPosition() const;
	sf::Transform getWorldTransform() const;

	void onCommand( const Command& command, sf::Time delta );
	virtual unsigned int getCategory() const;

	void checkSceneCollision( SceneNode& sceneGrath, std::set< Pair >& collisionPairs );
	void checkNodeCollision( SceneNode& node, std::set< Pair >& collisionPairs );
	void removeCorpses();
	virtual sf::FloatRect getBoundingRect() const;

	virtual bool isMarkedForRemoval() const;
	virtual bool isDestroyed() const;

private:
	virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const final;
	virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;

	void drawChildren( sf::RenderTarget& target, sf::RenderStates states ) const;

	virtual void updateCurrent( sf::Time delta, CommandQueue& commands );
	void updateChildren( sf::Time delta, CommandQueue& commands );

private:
	std::vector< Pointer > m_children;
	
	SceneNode* m_parent;
};

bool collision( const SceneNode& first, const SceneNode& second );
float distance( const SceneNode& first, const SceneNode& second );
