#include "player.hpp"

#include "command_queue.hpp"

#include "hero.hpp"

struct HeroMover
{
	HeroMover( float vx, float vy )
		:	velocity( vx, vy )
	{
	}

	void operator() ( Hero& hero, sf::Time ) const
	{
		hero.accelerate( velocity * hero.getMaxSpeed() );
	}

	sf::Vector2f velocity;
};

Player::Player()
	:	m_currentDemoStatus( DemoRunning )
{
	//Клавиши по умолчанию
	m_keyBinding[ sf::Keyboard::A ] = MoveLeft;
	m_keyBinding[ sf::Keyboard::D ] = MoveRight;
	m_keyBinding[ sf::Keyboard::W ] = MoveForward;
	m_keyBinding[ sf::Keyboard::S ] = MoveBack;

	m_keyBinding[ sf::Keyboard::Space ] = Attack;

	m_keyBinding[ sf::Keyboard::E ] = Interact;
	m_keyBinding[ sf::Keyboard::Z ] = ChangeScale;

	initializeActions();

	for ( auto& pair : m_actionBinding )
		pair.second.category = Category::Hero;
}

void Player::handleEvent( const sf::Event sfevent, CommandQueue& commands )
{
	if ( sfevent.type == sf::Event::KeyPressed )
	{
		//Если нажатая клавиша есть в списке забинденных клавиш и действие помечено как ивент, вызвать команду
		auto find = m_keyBinding.find( sfevent.key.code );
		if ( find != m_keyBinding.end() && !isRealTimeAction( find->second ) )
			commands.add( m_actionBinding[ find->second ] );
	}
}

void Player::handleRealTimeInput( CommandQueue& commands )
{
	for ( auto pair : m_keyBinding )
	{
		//если действие помечено как realtime
		if ( sf::Keyboard::isKeyPressed( pair.first ) && isRealTimeAction( pair.second ) )
			commands.add( m_actionBinding[ pair.second ] );
	}
}

void Player::bindKey( Action action, sf::Keyboard::Key key )
{
	for ( auto itr = m_keyBinding.begin(); itr != m_keyBinding.end(); )
	{
		if ( itr->second == action )
			m_keyBinding.erase( itr++ );
		else
			itr++;
	}

	m_keyBinding[ key ] = action;
}

sf::Keyboard::Key Player::getBoundKey( Action action ) const
{
	for ( auto pair : m_keyBinding )
	{
		if ( pair.second == action )
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::initializeActions()
{
	m_actionBinding[ MoveLeft ].action = obtainedAction< Hero >( HeroMover( -1.f, 0.f ) );
	m_actionBinding[ MoveRight ].action = obtainedAction< Hero >( HeroMover( +1.f, 0.f ) );
	m_actionBinding[ MoveForward ].action = obtainedAction< Hero >( HeroMover( 0.f, -1.f ) );
	m_actionBinding[ MoveBack ].action = obtainedAction< Hero >( HeroMover( 0.f, +1.f ) );

	m_actionBinding[ Attack ].action = obtainedAction< Hero >([] ( Hero& a, sf::Time delta ) { a.attack(); } );

	m_actionBinding[ Interact ].action = obtainedAction< Hero >([] ( Hero& a, sf::Time delta ) { a.interact(); } );
	m_actionBinding[ ChangeScale ].action = obtainedAction< Hero >([] ( Hero& a, sf::Time delta ) { a.interact(); } );
}

bool Player::isRealTimeAction( Action action )
{
	switch ( action )
	{
	case MoveLeft:
	case MoveRight:
	case MoveForward:
	case MoveBack:
		return true;

	case Interact:
		return false;

	case Attack:
		return true;

	case ChangeScale:
		return false;

	default:
		return false;
	}
}

void Player::setDemoStatus( DemoStatus status )
{
	m_currentDemoStatus = status;
}

Player::DemoStatus Player::getDemoStatus() const
{
	return m_currentDemoStatus;
}