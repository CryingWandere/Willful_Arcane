#pragma warning( disable : 4996 )

#include "label.hpp"

#include "utilities.hpp"
#include "color_identify.hpp"

#include < SFML/Graphics/RenderStates.hpp >
#include < SFML/Graphics/RenderTarget.hpp >

namespace GUI
{

Label::Label( const std::wstring& text, const FontHolder& fonts )
	:	m_text( text, fonts.get( Fonts::RetroGaming ), 30 )
{
	m_text.setColor( getColor( Colors::GUI_active ) );

	centerOrigin( m_text );
;}

bool Label::isSelectable() const
{
	return false;
}

void Label::handleEvent( const sf::Event& sfevent )
{
}

void Label::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
	states.transform *= getTransform();
	target.draw( m_text, states );
}

void Label::setText( const std::wstring& text )
{
	m_text.setString( text );
	centerOrigin( m_text );
}

void Label::setCharacterSize( int size )
{
	m_text.setCharacterSize( size );
	centerOrigin( m_text );
}

void Label::setColor( sf::Color color )
{
	m_text.setColor( color );
	centerOrigin( m_text );
}

}