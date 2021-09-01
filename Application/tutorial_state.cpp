#include "tutorial_state.hpp"

TutorialState::TutorialState( StateStack& stack, Context context )
	:	State( stack, context )
	,	m_world( *context.window, *context.fonts )
	,	m_player( *context.player )
{
}

void TutorialState::draw()
{
	m_world.draw();
}

bool TutorialState::update( sf::Time delta )
{
	m_world.update( delta );

	CommandQueue& commands = m_world.getCommandQueue();
	m_player.handleRealTimeInput( commands );

	Bools::Time::increaseGLobalTimer( delta );

	return true;
}

bool TutorialState::handleEvent( const sf::Event& sfevent )
{
	CommandQueue& commands = m_world.getCommandQueue();
	m_player.handleEvent( sfevent, commands );

	if ( sfevent.type == sf::Event::KeyPressed && sfevent.key.code == sf::Keyboard::Escape )
		requestStatePush( States::PauseMenu );

	if ( Dialogue::getConv() && Bools::Hero::getInteract() )
		requestStatePush( States::Dialogue );

	return true;
}