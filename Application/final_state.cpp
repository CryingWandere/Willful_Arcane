#pragma warning( disable : 4996 )

#include "final_state.hpp"

#include "player.hpp"
#include "label.hpp"
#include "button.hpp"
#include "resource_holder.hpp"
#include "color_identify.hpp"
#include "utilities.hpp"

#include < SFML/Graphics/RectangleShape.hpp >
#include < SFML/Graphics/RenderWindow.hpp >
#include < SFML/Graphics/View.hpp >

FinalState::FinalState( StateStack& stack, Context context )
	:	State( stack, context )
	,	m_gameOverText()
	,	m_container()
{
	sf::Font& font = context.fonts->get( Fonts::RetroGaming );
	m_gameOverText.setFont( font );
	m_gameOverText.setColor( getColor( Colors::Font_muted ) );
	centerOrigin( m_gameOverText );
	m_gameOverText.setPosition( 960.f, 250.f );

	if ( context.player->getDemoStatus() == Player::DemoFailure )
	{
		m_gameOverText.setString(L"Вы проиграли. Спасибо за игру в демоверсию.");
		centerOrigin( m_gameOverText );
	}
	else
	{
		m_gameOverText.setString( L"Поздравляем! Вы прошли демоверсию!" );
		centerOrigin( m_gameOverText );

		auto pretime = std::make_shared< GUI::Label >( L"Время прохождения:", *context.fonts );
		pretime->setPosition( sf::Vector2f( 960.f, 350.f ) );

		std::wstring temp =			std::to_wstring( static_cast< int >(			  trunc( Bools::Time::getGlobalTimer().asSeconds()   / 60  ) ) ) + L":";
				 if ( ( static_cast< int >( Bools::Time::getGlobalTimer().asSeconds() ) % 60 ) < 10 )
					 temp += L"0" + std::to_wstring( static_cast< int >( static_cast< int >( Bools::Time::getGlobalTimer().asSeconds() ) % 60    ) ) + L".";
				 else
					 temp +=		std::to_wstring( static_cast< int >( static_cast< int >( Bools::Time::getGlobalTimer().asSeconds() ) % 60	 ) ) + L".";
				 if		 ( ( static_cast< int >( Bools::Time::getGlobalTimer().asMilliseconds() ) % 1000 ) < 10    )
						 temp += L"00" + std::to_wstring( static_cast< int >( static_cast< int >( Bools::Time::getGlobalTimer().asMilliseconds() ) % 1000 ) );
				 else if ( ( static_cast< int >( Bools::Time::getGlobalTimer().asMilliseconds() ) % 1000 ) < 100   )
					 	 temp +=  L"0" + std::to_wstring( static_cast< int >( static_cast< int >( Bools::Time::getGlobalTimer().asMilliseconds() ) % 1000 ) );
				 else
						 temp +=         std::to_wstring( static_cast< int >( static_cast< int >( Bools::Time::getGlobalTimer().asMilliseconds() ) % 1000 ) );

		auto totaltime = std::make_shared< GUI::Label >( temp, *context.fonts );
		totaltime->setPosition( sf::Vector2f( 960.f, 450.f ) );

		m_container.pack( pretime );
		m_container.pack( totaltime );
	}

	auto backButton = std::make_shared< GUI::Button >( *context.fonts, *context.textures );
	backButton->setPosition( 960.f, 930.f );
	backButton->setText( L"НАЗАД" );
	backButton->setCallback( [ this ]()
	{
		requestStatePush( States::Warning_ETD );
	} );

	m_container.pack( backButton );
}

void FinalState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView( window.getDefaultView() );

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor( getColor( Colors::Menu_background ) );
	backgroundShape.setSize( window.getView().getSize() );

	window.draw( backgroundShape );
	window.draw( m_gameOverText );
	window.draw( m_container );
}

bool FinalState::update( sf::Time delta )
{
	return true;
}

bool FinalState::handleEvent( const sf::Event& sfevent )
{
	if ( sfevent.type == sf::Event::KeyPressed && sfevent.key.code == sf::Keyboard::Escape )
	{
		requestStatePop();
		requestStatePush( States::MainMenu );
	}

	m_container.handleEvent( sfevent );
	return false;
}