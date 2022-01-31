#pragma once

#include "component.hpp"
#include "resource_identify.hpp"
#include "resource_holder.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string>

namespace GUI
{

class Label : public Component
{
public:
	typedef std::shared_ptr< Label > Pointer;

public:
	Label( const std::wstring& text, const FontHolder& fonts );

	virtual bool isSelectable() const;
	void setText( const std::wstring& text );
	void setCharacterSize( int size );
	void setColor( sf::Color color );

	virtual void handleEvent( const sf::Event& sfevent );

private:
	void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

private:
	sf::Text m_text;
};

}
