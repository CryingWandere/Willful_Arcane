#pragma once

#include "state.hpp"
#include "state_identify.hpp"
#include "resource_identify.hpp"

#include < SFML/System/NonCopyable.hpp >
#include < SFML/System/Time.hpp >

#include < vector >
#include < map >
#include < functional >

//Forward declaration
namespace sf
{
	class Event;
	class RenderWindow;
}

class StateStack : private sf::NonCopyable
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};

public:
	explicit StateStack( State::Context context );

	template < typename T >
	void registerState( States::ID stateID );

	void update( sf::Time delta );
	void draw();
	void handleEvent( const sf::Event& sfevent );

	void pushState( States::ID stateID );
	void popState();
	void clearStates();

	bool isEmpty() const;

private:
	State::Pointer createState( States::ID stateID );
	void applyPendingChanges();

private:
	struct PendingChange
	{
		explicit PendingChange( Action action, States::ID stateID = States::None );

		Action action;
		States::ID stateID;
	};

private:
	std::vector< State::Pointer > m_stack;
	std::vector< PendingChange > m_pendingList;

	State::Context m_context;

	std::map< States::ID, std::function< State::Pointer() > > m_factories;
};


template < typename T >
void StateStack::registerState( States::ID stateID )
{
	m_factories[ stateID ] = [this] ()
	{
		return State::Pointer( new T( *this, m_context ) );
	};
}