#include "container.hpp"

#include  < SFML/Window/Event.hpp >
#include < SFML/Graphics/RenderStates.hpp >
#include < SFML/Graphics/RenderTarget.hpp >

namespace GUI
{

Container::Container()
	:	m_children()
	,	m_selectedChild( -1 )
{
}

void Container::pack( Component::Pointer component )
{
	m_children.push_back( component );

	if ( !hasSelection() && component->isSelectable() )
		select( m_children.size() - 1 );
}

bool Container::isSelectable() const
{
	return false;
}

void Container::handleEvent( const sf::Event& sfevent )
{
	//for children
	if ( hasSelection() && m_children[ m_selectedChild ]->isActive() )
		{
			m_children[ m_selectedChild ]->handleEvent( sfevent );
		}
	else if ( sfevent.type == sf::Event::KeyPressed )
	{
		if (		 sfevent.key.code == sf::Keyboard::W
				  || sfevent.key.code == sf::Keyboard::Up
				  || sfevent.key.code == sf::Keyboard::A
				  || sfevent.key.code == sf::Keyboard::Left )
		{
			selectPrevious();
		}
		else if (    sfevent.key.code == sf::Keyboard::S
				  || sfevent.key.code == sf::Keyboard::Down
				  || sfevent.key.code == sf::Keyboard::D
				  || sfevent.key.code == sf::Keyboard::Right )
		{
			selectNext();
		}
		else if (    sfevent.key.code == sf::Keyboard::Space
				  || sfevent.key.code == sf::Keyboard::Return )
		{
			if ( hasSelection() )
				m_children[ m_selectedChild ]->activate();
		}
	}
}

void Container::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
	states.transform *= getTransform();

	for ( const Component::Pointer& child : m_children )
		target.draw( *child, states );
}

bool Container::hasSelection() const
{
	return m_selectedChild >= 0;
}

void Container::select( std::size_t index )
{
	if ( m_children[index]->isSelectable() )
	{
		if ( hasSelection() )
			m_children[ m_selectedChild ]->deselect();

		m_children[ index ]->select();
		m_selectedChild = index;
	}
}

void Container::selectNext()
{
	if ( !hasSelection() )
		return;

	int next = m_selectedChild;

	do
		next = ( next + 1 ) % m_children.size();
	while ( !m_children[ next ]->isSelectable() );

	select( next );
}

void Container::selectPrevious()
{
	if ( !hasSelection() )
		return;

	int previous = m_selectedChild;

	do
		previous = ( previous + m_children.size() - 1 ) % m_children.size();
	while ( !m_children[ previous ]->isSelectable() );

	select( previous );
}

}