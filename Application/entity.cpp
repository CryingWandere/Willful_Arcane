#include "entity.hpp"

#include < cassert >

Entity::Entity( int hitpoints )
	:	m_velocity()
	,	m_hitpoints( hitpoints )
{

}

void Entity::setVelocity( sf::Vector2f velocity )
{
	m_velocity = velocity;
}

void Entity::setVelocity( float vx, float vy )
{
	m_velocity.x = vx;
	m_velocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return m_velocity;
}

void Entity::accelerate( sf::Vector2f velocity )
{
	m_velocity += velocity;
}

void Entity::accelerate( float vx, float vy )
{
	m_velocity.x += vx;
	m_velocity.y += vy;
}

int Entity::getHitpoints() const
{
	return m_hitpoints;
}

void Entity::heal( int hitpoints )
{
	assert( hitpoints > 0 );

	m_hitpoints += hitpoints;
}

void Entity::damage( int hitpoints )
{
	assert( hitpoints > 0 );

	m_hitpoints -= hitpoints;
}

void Entity::destroy()
{
	m_hitpoints = 0;
}

bool Entity::isDestroyed() const
{
	return m_hitpoints <= 0;
}

void Entity::updateCurrent( sf::Time delta, CommandQueue& commands )
{
	move( m_velocity * delta.asSeconds() );
}