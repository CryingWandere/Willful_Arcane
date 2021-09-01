#pragma once

#include "category.hpp"

#include < SFML/System/Time.hpp >

#include < cassert >
#include < functional >

class SceneNode;

struct Command
{
	Command();

	std::function< void( SceneNode&, sf::Time ) > action;

	unsigned int category;
};


template < typename GameObject, typename Function >
std::function< void( SceneNode&, sf::Time ) > obtainedAction( Function func )
{
	return [=]( SceneNode& node, sf::Time delta )
	{
		assert( dynamic_cast< GameObject* >( &node ) != nullptr );

		//Downcast
		func( static_cast< GameObject& >( node ), delta );
	};
}