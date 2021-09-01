#pragma warning( disable : 4996 )

#include "dialogue_button.hpp"

#include "dialogue_button.hpp"

#include "utilities.hpp"
#include "color_identify.hpp"

#include < SFML/Window/Event.hpp >
#include < SFML/Graphics/RenderStates.hpp >
#include < SFML/Graphics/RenderTarget.hpp >

namespace GUI
{

DialogueButton::DialogueButton( const FontHolder& fonts, const TextureHolder& textures )
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

void DialogueButton::setCallback( Callback callback )
{
	m_callback = std::move( callback );
}

void DialogueButton::setText( const std::wstring& text )
{
	m_text.setString( text );
	centerOrigin( m_text );
}

void DialogueButton::setToggle( bool flag )
{
	m_isToggle = flag;
}

bool DialogueButton::isSelectable() const
{
	return true;
}

void DialogueButton::select()
{
	Component::select();

	m_sprite.setTexture( m_selectedTexture );
	m_text.setColor( getColor( Colors::GUI_active ) );
}

void DialogueButton::deselect()
{
	Component::deselect();

	m_sprite.setTexture( m_defaultTexture );
	m_text.setColor( getColor( Colors::GUI_inactive ) );
}

void DialogueButton::activate()
{
	Component::activate();

	if ( m_isToggle )
		m_sprite.setTexture( m_pressedTexture );

	if ( m_callback )
		m_callback();

	if ( !m_isToggle )
		deactivate();
}

void DialogueButton::deactivate()
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

void DialogueButton::handleEvent( const sf::Event& sfevent )
{
}

void DialogueButton::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
	states.transform *= getTransform();

	target.draw( m_sprite, states );
	target.draw( m_text, states );
}

}