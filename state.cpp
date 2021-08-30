#include "state.hpp"
#include "state_stack.hpp"

State::Context::Context( sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player )
	:	window( &window )
	,	textures( &textures )
	,	fonts( &fonts )
	,	player( &player )
{
}

State::State( StateStack& stack, Context context )
	:	m_stack( &stack )
	,	m_context( context )
{
}

State::~State()
{
}

void State::requestStatePush( States::ID stateID )
{
	m_stack->pushState( stateID );
}

void State::requestStatePop()
{
	m_stack->popState();
}

void State::requestStateClear()
{
	m_stack->clearStates();
}

State::Context State::getContext() const
{
	return m_context;
}