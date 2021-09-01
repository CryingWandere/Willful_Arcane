#pragma warning( disable : 4996 )

#include "text_node.hpp"
#include "utilities.hpp"

#include < SFML/Graphics/RenderTarget.hpp >

TextNode::TextNode( const FontHolder& fonts, const std::wstring& text )
{
	m_text.setFont( fonts.get( Fonts::RetroGaming ) );
	m_text.setCharacterSize( 20 );
	m_text.setColor( sf::Color::Color( 0xea, 0xe6, 0xca, 192 ) );
	m_text.setOutlineColor( sf::Color::Color( 0x00, 0x00, 0x00, 144 ) );
	m_text.setOutlineThickness( 1 );
	setString( text );
}

void TextNode::drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const
{
	target.draw( m_text, states );
}

void TextNode::setString( const std::wstring& text )
{
	m_text.setString( text );

	centerOrigin( m_text );
}