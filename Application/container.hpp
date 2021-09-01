#pragma once

#include "component.hpp"

#include < memory >
#include < vector >

namespace GUI
{

class Container : public Component
{
public:
	Container();

	void pack( Component::Pointer component );

	virtual bool isSelectable() const;

	virtual void handleEvent( const sf::Event& sfevent );

private:
	virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

	bool hasSelection() const;
	
	void select( std::size_t index );
	void selectNext();
	void selectPrevious();

private:
	std::vector< Component::Pointer > m_children;
	int m_selectedChild;
};

}