#pragma once

//Wrong key selected

#include "state.hpp"
#include "container.hpp"

#include < SFML/Graphics/Sprite.hpp >
#include < SFML/Graphics/Text.hpp >

class AlertState : public State
{
public:
	AlertState( StateStack& stack, Context context );

	virtual void draw();
	virtual bool update( sf::Time delta );
	virtual bool handleEvent( const sf::Event& sfevent );

private:
	sf::Sprite m_windowSprite;

	GUI::Container m_container;
};