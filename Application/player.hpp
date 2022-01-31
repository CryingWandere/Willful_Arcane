#pragma once

#include "command.hpp"

#include <SFML/Window/Event.hpp>

#include <map>

//Forward declaration
class CommandQueue;

class Player
{
public:
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveForward,
		MoveBack,

		Attack,

		Interact,
		ChangeScale,

		TotalActions
	};

	enum DemoStatus
	{
		DemoRunning,
		DemoSuccess,
		DemoFailure
	};

public:
	Player();

	void handleEvent( const sf::Event, CommandQueue& commands );
	void handleRealTimeInput( CommandQueue& commands );

	void bindKey( Action action, sf::Keyboard::Key key );
	sf::Keyboard::Key getBoundKey( Action action ) const;

	void setDemoStatus( DemoStatus status );
	DemoStatus getDemoStatus() const;


private:
	void initializeActions();
	static bool isRealTimeAction( Action action );

private:
	std::map< sf::Keyboard::Key, Action > m_keyBinding;
	std::map< Action, Command > m_actionBinding;

	DemoStatus m_currentDemoStatus;
};
