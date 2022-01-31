#pragma once

//Exit to desktop

#include "state.hpp"
#include "container.hpp"

#include "resource_identify.hpp"
#include "resource_holder.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class WarningState : public State
{
public:
	WarningState( StateStack& stack, Context context );

	virtual void draw();
	virtual bool update( sf::Time delta );
	virtual bool handleEvent( const sf::Event& sfevent );

private:
	sf::Sprite m_windowSprite;

	GUI::Container m_container;
};
