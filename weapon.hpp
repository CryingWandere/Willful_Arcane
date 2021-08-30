#pragma once

#include "entity.hpp"
#include "resource_identify.hpp"

#include < SFML/Graphics/Sprite.hpp >

class Weapon : public Entity
{
public:
	enum Type
	{
		Sword,
		EnemySword,

		Total
	};

public:
	Weapon( Type type, const TextureHolder& textures );

	virtual unsigned int getCategory() const;
	virtual sf::FloatRect getBoundingRect() const;

	int getDamage() const;

private:
	virtual void updateCurrent( sf::Time delta, CommandQueue& commands );
	virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;

private:
	Type m_type;
	
	sf::Sprite m_sprite;
};