#pragma once

#include "state.hpp"

#include "bools.hpp"
#include "dialogue.hpp"

#include < SFML/Graphics/Sprite.hpp >
#include < SFML/Graphics/Text.hpp >

class WhiteState : public State
{
public:
	WhiteState( StateStack& stack, Context context );

	virtual void draw();
	virtual bool update( sf::Time delta );
	virtual bool handleEvent( const sf::Event& sfevent );

private:
	sf::Sprite m_windowSprite;

	sf::Time m_timer;
};