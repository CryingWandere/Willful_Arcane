#pragma once

#include "state.hpp"

#include "bools.hpp"
#include "container.hpp"

#include < SFML/Graphics/Sprite.hpp >
#include < SFML/Graphics/Text.hpp >

class FinalState : public State
{
public:
	FinalState( StateStack& stack, Context context );

	virtual void draw();
	virtual bool update( sf::Time delta );
	virtual bool handleEvent( const sf::Event& sfevent );

private:
	GUI::Container m_container;

	sf::Text m_gameOverText;
};