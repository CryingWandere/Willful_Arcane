#pragma warning( disable : 4996 )

#include "title_state.hpp"

#include "resource_holder.hpp"
#include "utilities.hpp"

#include < SFML/Graphics/RenderWindow.hpp >

TitleState::TitleState( StateStack& stack, Context context )
	:	State( stack, context )
	,	m_text()
	,	m_showText( true )
	,	m_textBlinkTime( sf::Time::Zero )
{
	m_backgroundSprite.setTexture( context.textures->get( Textures::TitleScreen ) );

	m_text.setFont( context.fonts->get( Fonts::RetroGaming ) );
	m_text.setString( L"ÍÀÆÌÈÒÅ ËÞÁÓÞ ÊËÀÂÈØÓ ÄËß ÏÐÎÄÎËÆÅÍÈß" );
	m_text.setOutlineColor( sf::Color::Black );
	m_text.setOutlineThickness( 1 );
	m_text.setCharacterSize( 30 );
	m_text.setColor( sf::Color::Color( 0xff, 0xff, 0xff, 250 ) );
	centerOrigin( m_text );
	m_text.setPosition( context.window->getSize().x / 2.f, context.window->getSize().y / 1.31 );
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw( m_backgroundSprite );

	if ( m_showText )
		window.draw( m_text );
}

bool TitleState::update( sf::Time delta )
{
	m_textBlinkTime += delta;

	if ( m_textBlinkTime >= sf::seconds( 0.7f ) && m_showText )
	{
		m_showText = false;
		m_textBlinkTime = sf::Time::Zero;
	}
	if ( m_textBlinkTime >= sf::seconds( 0.1f ) && !m_showText )
	{
		m_showText = true;
		m_textBlinkTime = sf::Time::Zero;
	}

	return true;
}

bool TitleState::handleEvent( const sf::Event& sfevent )
{
	if ( sfevent.type == sf::Event::KeyPressed )
	{
		requestStatePop();
		requestStatePush( States::MainMenu );
	}

	return true;
}