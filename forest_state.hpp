#pragma once

#include "state.hpp"
#include "forest.hpp"
#include "player.hpp"

#include "bools.hpp"

//#include "dialogue.hpp"

#include < SFML/Graphics/Sprite.hpp >
#include < SFML/Graphics/Text.hpp >

class ForestState : public State
{
public:
	ForestState( StateStack& stack, Context context );

	virtual void draw();
	virtual bool update( sf::Time delta );
	virtual bool handleEvent( const sf::Event& sfevent );

private:
	Forest m_forest;
	Player& m_player;

	sf::Time m_timer;
};