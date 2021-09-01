#include "npc.hpp"

#include "data_storage.hpp"
#include "command_queue.hpp"
#include "resource_holder.hpp"
#include "utilities.hpp"

//global region
namespace
{
	const std::vector< NPCData > Table = initializeNPCData();
}

NPC::NPC( Type type, const TextureHolder& textures, const FontHolder& fonts )
	:	Entity( Table[ type ].hitpoints )
	,	m_type( type )
	,	m_sprite( textures.get( Table[ type ].texture ) )
{
	centerOrigin( m_sprite );
}

void NPC::drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const
{
	target.draw( m_sprite, states );
}

void NPC::updateCurrent( sf::Time delta, CommandQueue& commands )
{
	Entity::updateCurrent( delta, commands );
}

sf::FloatRect NPC::getBoundingRect() const
{
	return getWorldTransform().transformRect( m_sprite.getGlobalBounds() );
}

unsigned int NPC::getCategory() const
{
	return Category::NPC;
}