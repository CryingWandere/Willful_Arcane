#pragma once

#include < SFML/Graphics.hpp >

#include "scene_node.hpp"

class Entity : public SceneNode
{
public:
	explicit Entity( int hitpoints );

	void heal( int hitpoints );
	void damage( int hitpoints );
	void destroy();

	int getHitpoints() const;
	bool isDestroyed() const;

	void setVelocity( sf::Vector2f velocity );
	void setVelocity( float vx, float vy );

	void accelerate( sf::Vector2f velocity );
	void accelerate( float vx, float vy );

	sf::Vector2f getVelocity() const;

protected:
	virtual void updateCurrent( sf::Time delta, CommandQueue& commands );

private:
	sf::Vector2f m_velocity;

	int m_hitpoints;

};