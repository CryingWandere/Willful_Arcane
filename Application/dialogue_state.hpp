#pragma once

#include "state.hpp"
#include "container.hpp"
#include "dialogue_button.hpp"
#include "label.hpp"

#include "world.hpp"
#include "player.hpp"

#include "dialogue.hpp"

#include "quotes_storage.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class DialogueState : public State
{
public:
	DialogueState( StateStack& stack, Context context );

	virtual void draw();
	virtual bool update( sf::Time delta );
	virtual bool handleEvent( const sf::Event& sfevent );

private:
	void addLabel( const std::wstring& text, Context context );

	enum ButtonType
	{
		Forward,
		Jump,
		End,
		Event,

		AllTypes
	};
	void addButton( ButtonType type, Quotes::ID jumpto, bool sendToRepeat, float pillar, const std::wstring& text, Context context );
	void addButtonSecond( ButtonType type, Quotes::ID jumpto, bool sendToRepeat, float pillar, const std::wstring& text, Context context );

	void errorOccured( Context context );

private:
	World m_world;

	sf::Sprite m_windowSprite;
	sf::Sprite m_warriorSprite;
	sf::Sprite m_peasantGirlSprite;

	GUI::Container m_container;

	std::vector< std::wstring > m_quotes;
	Quotes::ID m_quoteJumpTo;
	Quotes::ID m_quoteJumpToSecond;

	bool m_b_sendToRepeat;
};
