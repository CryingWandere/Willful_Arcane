#pragma warning( disable : 4996 )

#include "UTF8_label.hpp"

#include "utilities.hpp"
#include "color_identify.hpp"

#include < SFML/Graphics/RenderStates.hpp >
#include < SFML/Graphics/RenderTarget.hpp >

namespace GUI
{

UTF8Label::UTF8Label( const std::string& text, const FontHolder& fonts )
	:	m_text( text, fonts.get( Fonts::RetroGaming ), 30 )
{
	m_text.setColor( getColor( Colors::GUI_active ) );
}

bool UTF8Label::isSelectable() const
{
	return false;
}

void UTF8Label::handleEvent( const sf::Event& sfevent )
{
}

void UTF8Label::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
	states.transform *= getTransform();
	target.draw( m_text, states );
}

void UTF8Label::setText( const std::string& text )
{
	m_text.setString( text );
	centerOrigin( m_text );
}

}