#pragma once

#include "state.hpp"
#include "container.hpp"
#include "button.hpp"
#include "long_button.hpp"
#include "label.hpp"
#include "UTF8_label.hpp"

#include "player.hpp"

#include < SFML/Graphics/Sprite.hpp >
#include < SFML/Graphics/Text.hpp >

#include < array >
#include < string >

class KeyBindingsState : public State
{
public:
	KeyBindingsState( StateStack& stack, Context context );

	virtual void draw();
	virtual bool update( sf::Time delta );
	virtual bool handleEvent( const sf::Event& sfevent );

private:
	void updateLabels();
	void addButton( Player::Action action, float pillar, const std::wstring& text, Context context );

private:
	sf::Sprite m_backgroundSprite;

	GUI::Container m_container;

	std::array< GUI::LongButton::Pointer, Player::TotalActions > m_bindingButtons;
	std::array< GUI::UTF8Label::Pointer, Player::TotalActions > m_bindingLabels;
};