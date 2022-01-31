#pragma warning( disable : 4996 )

#include "pauseMenu_state.hpp"

#include "resource_holder.hpp"
#include "button.hpp"
#include "label.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

PauseMenuState::PauseMenuState( StateStack& stack, Context context )
	:	State( stack, context )
	,	m_backgroundSprite()
	,	m_container()
{
	auto continueButton = std::make_shared< GUI::Button >( *context.fonts, *context.textures );
	continueButton->setPosition( 960.f, 600.f );
	continueButton->setText( L"ПРОДОЛЖИТЬ" );
	continueButton->setCallback( [ this ]()
	{
		requestStatePop();
	} );

	auto settingsButton = std::make_shared< GUI::Button >( *context.fonts, *context.textures );
	settingsButton->setPosition( continueButton->getPosition() + sf::Vector2f( 0.f, 70.f ) );
	settingsButton->setText( L"НАСТРОЙКИ" );
	settingsButton->setCallback( [ this ]()
	{
		requestStatePush( States::Settings );
	} );

	auto toMainMenuButton = std::make_shared< GUI::Button >( *context.fonts, *context.textures );
	toMainMenuButton->setPosition( settingsButton->getPosition() + sf::Vector2f( 0.f, 70.f ) );
	toMainMenuButton->setText( L"ВЫЙТИ В ГЛАВНОЕ МЕНЮ" );
	toMainMenuButton->setCallback( [ this ]()
	{
		requestStateClear();
		requestStatePush( States::MainMenu );
	} );

	auto toDesktopButton = std::make_shared< GUI::Button >( *context.fonts, *context.textures );
	toDesktopButton->setPosition( toMainMenuButton->getPosition() + sf::Vector2f( 0.f, 70.f ) );
	toDesktopButton->setText( L"ВЫЙТИ НА РАБОЧИЙ СТОЛ" );
	toDesktopButton->setCallback( [ this ]()
	{
		requestStatePush( States::Warning_ETD );
	} );

	auto pauseLabel = std::make_shared< GUI::Label >( L"ИГРА ПРИОСТАНОВЛЕНА" , *context.fonts );
	pauseLabel->setPosition( continueButton->getPosition() - sf::Vector2f( 0.f, 230.f ) );

	m_container.pack( pauseLabel );

	m_container.pack( continueButton );
	m_container.pack( settingsButton );
	m_container.pack( toMainMenuButton );
	m_container.pack( toDesktopButton );
}

void PauseMenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView( window.getDefaultView() );

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor( sf::Color( 0, 0, 0, 128 ) );
	backgroundShape.setSize( window.getView().getSize() );

	window.draw( backgroundShape );
	window.draw( m_container );
}

bool PauseMenuState::update( sf::Time delta )
{
	return false;
}

bool PauseMenuState::handleEvent( const sf::Event& sfevent )
{
	if ( sfevent.type == sf::Event::KeyPressed && sfevent.key.code == sf::Keyboard::Escape )
		requestStatePop();

	m_container.handleEvent( sfevent );
	return false;
}
