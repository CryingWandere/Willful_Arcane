#pragma once

#include "state.hpp"
#include "container.hpp"

#include "label.hpp"
#include "button.hpp"
#include "long_button.hpp"

#include < SFML/Graphics/Sprite.hpp >
#include < SFML/Graphics/Text.hpp >

class ImageState : public State
{
public:
	ImageState( StateStack& stack, Context context );

	virtual void draw();
	virtual bool update( sf::Time delta );
	virtual bool handleEvent( const sf::Event& sfevent );

private:
	void updateLabels();

private:
	sf::Sprite m_backgroundSprite;

	GUI::Container m_container;

	GUI::Label::Pointer m_ShowDebugInfoLabel;
};
