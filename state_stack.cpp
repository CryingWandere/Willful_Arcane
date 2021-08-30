#include "state_stack.hpp"

#include < cassert >

StateStack::StateStack( State::Context context )
	:	m_stack()
	,	m_pendingList()
	,	m_context( context )
	,	m_factories()
{
}

void StateStack::update( sf::Time delta )
{
	for ( auto cntr = m_stack.rbegin(); cntr != m_stack.rend(); cntr++ )
	{
		if ( !( *cntr )->update( delta ) )
			break;
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	for ( State::Pointer& state : m_stack )
		state->draw();
}

void StateStack::handleEvent( const sf::Event& sfevent )
{
	for ( auto cntr = m_stack.rbegin(); cntr != m_stack.rend(); cntr++ )
	{
		if ( !( *cntr )->handleEvent( sfevent ) )
			break;
	}

	applyPendingChanges();
}

//Добавление сцены
void StateStack::pushState( States::ID stateID )
{
	m_pendingList.push_back( PendingChange( Push, stateID ) );
}

//Удаление сцены
void StateStack::popState()
{
	m_pendingList.push_back( PendingChange( Pop ) );
}

//Очистка вектора сцен
void StateStack::clearStates()
{
	m_pendingList.push_back( PendingChange( Clear ) );
}

//Если вектор сцен пуст
bool StateStack::isEmpty() const
{
	return m_stack.empty();
}

//Создание сцены
State::Pointer StateStack::createState( States::ID stateID )
{
	auto find = m_factories.find( stateID );
	assert( find != m_factories.end() );

	return find->second();
}

//Применение изменений только после отрисовки сцены
void StateStack::applyPendingChanges()
{
	for ( PendingChange pchange : m_pendingList )
	{
		switch ( pchange.action )
		{
		case Push:
			m_stack.push_back( createState( pchange.stateID ) );
			break;

		case Pop:
			m_stack.pop_back();
			break;

		case Clear:
			m_stack.clear();
			break;
		}
	}

	m_pendingList.clear();
}

StateStack::PendingChange::PendingChange( Action action, States::ID stateID )
	:	action ( action )
	,	stateID ( stateID )
{
}