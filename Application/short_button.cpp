#pragma warning( disable : 4996 )

#include "short_button.hpp"

#include "utilities.hpp"
#include "color_identify.hpp"

#include < SFML/Window/Event.hpp >
#include < SFML/Graphics/RenderStates.hpp >
#include < SFML/Graphics/RenderTarget.hpp >

namespace GUI
{

ShortButton::ShortButton( const FontHolder& fonts, const TextureHolder& textures )
	:	m_callback()
	,	m_lockedTexture( textures.get( Textures::LockedShortButton ) )
	,	m_defaultTexture( textures.get( Textures::DefaultShortButton ) )
	,	m_selectedTexture( textures.get( Textures::SelectedShortButton ) )
	,	m_pressedTexture( textures.get( Textures::PressedShortButton ) )
	,	m_sprite()
	,	m_text( "", fonts.get( Fonts::RetroGaming ), 30 )
	,	m_isToggle( false )
{
	m_sprite.setTexture( m_defaultTexture );
	centerOrigin( m_sprite );

	m_text.setColor( getColor( Colors::GUI_locked ) );
}

void ShortButton::setCallback( Callback callback )
{
	m_callback = std::move( callback );
}

void ShortButton::setText( const std::wstring& text )
{
	sf::FloatRect bounds = m_sprite.getLocalBounds();

	m_text.setString( text );
	centerOrigin( m_text );
}

void ShortButton::setToggle( bool flag )
{
	m_isToggle = flag;
}

bool ShortButton::isSelectable() const
{
	return true;
}

void ShortButton::select()
{
	Component::select();

	m_sprite.setTexture( m_selectedTexture );
	m_text.setColor( getColor( Colors::GUI_active ) );
}

void ShortButton::deselect()
{
	Component::deselect();

	m_sprite.setTexture( m_defaultTexture );
	m_text.setColor( getColor( Colors::GUI_locked ) );
}

void ShortButton::activate()
{
	Component::activate();

	if ( m_isToggle )
		m_sprite.setTexture( m_pressedTexture );

	if ( m_callback )
		m_callback();

	if ( !m_isToggle )
		deactivate();
}

void ShortButton::deactivate()
{
	Component::deactivate();

	if ( m_isToggle )
	{
		if ( isSelected() )
			m_sprite.setTexture( m_selectedTexture );
		else
			m_sprite.setTexture( m_defaultTexture );
	}
}

void ShortButton::handleEvent( const sf::Event& sfevent )
{
}

void ShortButton::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
	states.transform *= getTransform();

	target.draw( m_sprite, states );
	target.draw( m_text, states );
}
}