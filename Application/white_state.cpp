#include "white_state.hpp"

#include "utilities.hpp"
#include "resource_holder.hpp"

#include < SFML/Graphics/RenderWindow.hpp >
#include < SFML/Graphics/View.hpp >

WhiteState::WhiteState( StateStack& stack, Context context )
	:	State( stack, context )
	,	m_windowSprite()
	,	m_timer( sf::Time::Zero )
{
	sf::Texture& texture = context.textures->get( Textures::Flash01 );

	m_windowSprite.setTexture( texture );

	sf::RenderWindow& window = *getContext().window;
	window.setView( window.getDefaultView() );
}

void WhiteState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView( window.getDefaultView() );

	window.draw( m_windowSprite );
}

bool WhiteState::update( sf::Time delta )
{
	m_timer += delta;

	Bools::Time::increaseGLobalTimer( delta );

	return true;
}

bool WhiteState::handleEvent( const sf::Event& sfevent )
{
	if ( m_timer.asMilliseconds() >= 2000 )
	{
		requestStatePop();
		requestStatePush( States::Forest );
	}

	if ( sfevent.type == sf::Event::KeyPressed && sfevent.key.code == sf::Keyboard::Escape )
		requestStatePush( States::PauseMenu );

	return true;
}