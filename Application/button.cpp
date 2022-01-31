#pragma warning( disable : 4996 )

#include "button.hpp"

#include "utilities.hpp"
#include "color_identify.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{

Button::Button( const FontHolder& fonts, const TextureHolder& textures )
	:	m_callback()
	,	m_lockedTexture( textures.get( Textures::LockedButton ) )
	,	m_defaultTexture( textures.get( Textures::DefaultButton ) )
	,	m_selectedTexture( textures.get( Textures::SelectedButton ) )
	,	m_pressedTexture( textures.get( Textures::PressedButton ) )
	,	m_sprite()
	,	m_text( "", fonts.get( Fonts::RetroGaming ), 30 )
	,	m_isToggle( false )
{
	m_sprite.setTexture( m_defaultTexture );
	centerOrigin( m_sprite );

	m_text.setColor( getColor( Colors::GUI_inactive ) );
}

void Button::setCallback( Callback callback )
{
	m_callback = std::move( callback );
}

void Button::setText( const std::wstring& text )
{
	m_text.setString( text );
	centerOrigin( m_text );
}

void Button::setToggle( bool flag )
{
	m_isToggle = flag;
}

bool Button::isSelectable() const
{
	return true;
}

void Button::select()
{
	Component::select();

	m_sprite.setTexture( m_selectedTexture );
	m_text.setColor( getColor( Colors::GUI_active ) );
}

void Button::deselect()
{
	Component::deselect();

	m_sprite.setTexture( m_defaultTexture );
	m_text.setColor( getColor( Colors::GUI_inactive ) );
}

void Button::activate()
{
	Component::activate();

	if ( m_isToggle )
		m_sprite.setTexture( m_pressedTexture );

	if ( m_callback )
		m_callback();

	if ( !m_isToggle )
		deactivate();
}

void Button::deactivate()
{
	Component::deactivate();

	if ( m_isToggle )
	{
		//Return old texture
		if ( isSelected() )
			m_sprite.setTexture( m_selectedTexture );
		else
			m_sprite.setTexture( m_defaultTexture );
	}
}

void Button::handleEvent( const sf::Event& sfevent )
{
}

void Button::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
	states.transform *= getTransform();

	target.draw( m_sprite, states );
	target.draw( m_text, states );
}

}
