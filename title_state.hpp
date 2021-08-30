#pragma once

#include "state.hpp"

#include < SFML/Graphics/Sprite.hpp >
#include < SFML/Graphics/Text.hpp >

class TitleState : public State
{
public:
	TitleState( StateStack& stack, Context context );

	virtual void draw();
	virtual bool update( sf::Time delta );
	virtual bool handleEvent( const sf::Event& sfevent );

private:
	sf::Sprite m_backgroundSprite;
	sf::Text m_text;

	bool m_showText;
	sf::Time m_textBlinkTime;
};