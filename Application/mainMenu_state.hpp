#pragma once

#include "state.hpp"
#include "container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class MainMenuState : public State
{
public:
	MainMenuState( StateStack& stack, Context context );

	virtual void draw();
	virtual bool update( sf::Time delta );
	virtual bool handleEvent( const sf::Event& sfevent );

private:
	sf::Sprite m_backgroundSprite;

	GUI::Container m_container;
};
