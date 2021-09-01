#include "weapon.hpp"

#include "data_storage.hpp"
#include "utilities.hpp"
#include "resource_holder.hpp"

#include < SFML/Graphics/RenderTarget.hpp >
#include < SFML/Graphics/RenderStates.hpp >

//global region
namespace
{
	const std::vector< WeaponData > Table = initializeWeaponData();
}

Weapon::Weapon( Type type, const TextureHolder& textures )
	:	Entity( 1 )
	,	m_type( type )
	,	m_sprite( textures.get( Table[ type ].texture ) )
{
	centerOrigin( m_sprite );
}

void Weapon::updateCurrent( sf::Time delta, CommandQueue& commands )
{
	Entity::updateCurrent( delta, commands );
}

void Weapon::drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const
{
	target.draw( m_sprite, states );
}

unsigned int Weapon::getCategory() const
{
	switch ( m_type )
	{
	case Weapon::Sword:				return Category::AlliedWeapon;
	case Weapon::EnemySword:		return Category::EnemyWeapon;
	}
}

sf::FloatRect Weapon::getBoundingRect() const
{
	return getWorldTransform().transformRect( m_sprite.getGlobalBounds() );
}

int Weapon::getDamage() const
{
	return Table[ m_type ].damage;
}