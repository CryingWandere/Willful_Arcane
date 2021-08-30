#pragma once

#include "resource_holder.hpp"
#include "resource_identify.hpp"
#include "scene_node.hpp"

#include < SFML/Graphics/Text.hpp >
#include < SFML/Graphics/Font.hpp >

class TextNode : public SceneNode
{
public:
	explicit TextNode( const FontHolder& fonts, const std::wstring& text );

	void setString( const std::wstring& text );

private:
	virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;
	
private:
	sf::Text m_text;
};