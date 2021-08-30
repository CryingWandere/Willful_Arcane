#include "forest_state.hpp"

ForestState::ForestState( StateStack& stack, Context context )
	:	State( stack, context )
	,	m_forest( *context.window, *context.fonts )
	,	m_player( *context.player )
	,	m_timer( sf::Time::Zero )
{
}

void ForestState::draw()
{
	m_forest.draw();
}

bool ForestState::update( sf::Time delta )
{
	m_forest.update( delta );

	if ( not m_forest.hasAliveHero() )
	{
		requestStatePop();
		m_player.setDemoStatus( Player::DemoFailure );
		requestStatePush( States::Final );
	}

	if ( m_forest.hasHeroWon() )
	{
		requestStatePop();
		m_player.setDemoStatus( Player::DemoSuccess );
		requestStatePush( States::Final );
	}


	CommandQueue& commands = m_forest.getCommandQueue();
	m_player.handleRealTimeInput( commands );

	Bools::Time::increaseGLobalTimer( delta );

	return true;
}

bool ForestState::handleEvent( const sf::Event& sfevent )
{
	CommandQueue& commands = m_forest.getCommandQueue();
	m_player.handleEvent( sfevent, commands );

	if ( sfevent.type == sf::Event::KeyPressed && sfevent.key.code == sf::Keyboard::Escape )
		requestStatePush( States::PauseMenu );

	return true;
}