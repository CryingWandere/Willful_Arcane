#pragma once

#include "component.hpp"
#include "resource_identify.hpp"
#include "resource_holder.hpp"

#include < SFML/Graphics/Text.hpp >

#include < string >

namespace GUI
{

class UTF8Label : public Component
{
public:
	typedef std::shared_ptr< UTF8Label > Pointer;

public:
	UTF8Label( const std::string& text, const FontHolder& fonts );

	virtual bool isSelectable() const;
	void setText( const std::string& text );

	virtual void handleEvent( const sf::Event& sfevent );

private:
	void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

private:
	sf::Text m_text;
};

}