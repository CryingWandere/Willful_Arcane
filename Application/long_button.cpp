#pragma warning( disable : 4996 )

#include "long_button.hpp"

#include "utilities.hpp"
#include "color_identify.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{

LongButton::LongButton( const FontHolder& fonts, const TextureHolder& textures )
	:	m_callback()
	,	m_defaultTexture( textures.get( Textures::DefaultLongButton ) )
	,	m_selectedTexture( textures.get( Textures::SelectedLongButton ) )
	,	m_pressedTexture( textures.get( Textures::PressedLongButton ) )
	,	m_sprite()
	,	m_text( "", fonts.get( Fonts::RetroGaming ), 30 )
	,	m_isToggle( false )
{
	m_sprite.setTexture( m_defaultTexture );
	centerOrigin( m_sprite );

	sf::FloatRect bounds = m_text.getLocalBounds();
	m_text.setPosition( bounds.width / 2.f, bounds.height / 2.f );
	m_text.setColor( getColor( Colors::GUI_inactive ) );
}

void LongButton::setCallback( Callback callback )
{
	m_callback = std::move( callback );
}

void LongButton::setText( const std::wstring& text )
{
	m_text.setString( text );
	centerOrigin( m_text );
	m_text.setPosition( -300.f, 0.f );
}

void LongButton::setToggle( bool flag )
{
	m_isToggle = flag;
}

bool LongButton::isSelectable() const
{
	return true;
}

void LongButton::select()
{
	Component::select();

	m_sprite.setTexture( m_selectedTexture );
	m_text.setColor( getColor( Colors::GUI_active ) );
}

void LongButton::deselect()
{
	Component::deselect();

	m_sprite.setTexture( m_defaultTexture );
	m_text.setColor( getColor( Colors::GUI_inactive ) );
}

void LongButton::activate()
{
	Component::activate();

	if ( m_isToggle )
		m_sprite.setTexture( m_pressedTexture );

	if ( m_callback )
		m_callback();

	if ( !m_isToggle )
		deactivate();
}

void LongButton::deactivate()
{
	Component::deactivate();

	if ( m_isToggle )
	{
		//
		if ( isSelected() )
			m_sprite.setTexture( m_selectedTexture );
		else
			m_sprite.setTexture( m_defaultTexture );
	}
}

void LongButton::handleEvent( const sf::Event& sfevent )
{
}

void LongButton::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
	states.transform *= getTransform();

	target.draw( m_sprite, states );
	target.draw( m_text, states );
}

}