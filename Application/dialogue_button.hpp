#pragma once

#include "component.hpp"
#include "resource_identify.hpp"
#include "resource_holder.hpp"

#include < SFML/Graphics/Sprite.hpp >
#include < SFML/Graphics/Text.hpp >

#include < functional >
#include < string >

namespace GUI
{

class DialogueButton : public Component
{
public:
	typedef std::shared_ptr< DialogueButton > Pointer;
	typedef std::function< void() > Callback;

public:
	DialogueButton( const FontHolder& fonts, const TextureHolder& textures );

	void setCallback( Callback callback );
	void setText( const std::wstring& text );
	void setToggle( bool flag );

	virtual bool isSelectable() const;
	virtual void select();
	virtual void deselect();

	virtual void activate();
	virtual void deactivate();

	virtual void handleEvent( const sf::Event& sfevent );

private:
	virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

private:
	Callback m_callback;

	const sf::Texture& m_defaultTexture;
	const sf::Texture& m_selectedTexture;
	const sf::Texture& m_pressedTexture;

	sf::Sprite m_sprite;
	sf::Text m_text;

	bool m_isToggle;
};

}