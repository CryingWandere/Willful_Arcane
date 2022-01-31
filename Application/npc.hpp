#pragma once

#include "entity.hpp"
#include "command.hpp"
#include "command_queue.hpp"
#include "resource_identify.hpp"
#include "text_node.hpp"

#include <SFML/Graphics/Sprite.hpp>

class NPC : public Entity
{
public:
	enum Type
	{
		PeasantGirl,

		AllNPCs
	};

public:
	NPC( Type type, const TextureHolder& textures, const FontHolder& fonts );

	virtual unsigned int getCategory() const;
	virtual sf::FloatRect getBoundingRect() const;

private:
	virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;
	virtual void updateCurrent( sf::Time delta, CommandQueue& commands );

private:
	Type m_type;

	sf::Sprite m_sprite;
};
