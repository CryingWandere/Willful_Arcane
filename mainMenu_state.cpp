#pragma warning( disable : 4996 )

#include "mainMenu_state.hpp"

#include "button.hpp"
#include "resource_holder.hpp"

#include "bools.hpp"

#include < SFML/Graphics/RenderWindow.hpp >
#include < SFML/Graphics/View.hpp >

MainMenuState::MainMenuState( StateStack& stack, Context context )
	:	State( stack, context )
	,	m_container()
{
	Bools::Time::setGlobalTimer( sf::Time::Zero );

	sf::Texture& texture = context.textures->get( Textures::MainMenuScreen );

	m_backgroundSprite.setTexture( texture );
	
	auto loadButton = std::make_shared< GUI::Button >( *context.fonts, *context.textures );
	loadButton->setPosition( 960.f, 500.f );
	loadButton->setText( L"ÇÀÃÐÓÇÈÒÜ ÈÃÐÓ" );
	loadButton->setCallback( [ this ]()
	{
	} );

	auto playButton = std::make_shared< GUI::Button >( *context.fonts, *context.textures );
	playButton->setPosition( loadButton->getPosition() + sf::Vector2f( 0.f, 70.f ) );
	playButton->setText( L"ÍÎÂÀß ÈÃÐÀ" );
	playButton->setCallback( [ this ]()
	{
		requestStatePop();
		requestStatePush( States::Tutorial );
	} );

	auto settingsButton = std::make_shared< GUI::Button >( *context.fonts, *context.textures );
	settingsButton->setPosition( playButton->getPosition() + sf::Vector2f( 0.f, 70.f ) );
	settingsButton->setText( L"ÏÀÐÀÌÅÒÐÛ" );
	settingsButton->setCallback( [ this ]()
	{
		requestStatePush( States::Settings );
	} );

	auto creditsButton = std::make_shared< GUI::Button >( *context.fonts, *context.textures );
	creditsButton->setPosition( settingsButton->getPosition() + sf::Vector2f( 0.f, 70.f ) );
	creditsButton->setText( L"ÑÎÇÄÀÒÅËÈ" );
	creditsButton->setCallback( [ this ]()
	{
		requestStatePop();
		requestStatePush( States::Credits );
	} );

	auto exitButton = std::make_shared< GUI::Button >( *context.fonts, *context.textures );
	exitButton->setPosition( creditsButton->getPosition() + sf::Vector2f( 0.f, 70.f ) );
	exitButton->setText( L"ÂÛÉÒÈ ÍÀ ÐÀÁÎ×ÈÉ ÑÒÎË" );
	exitButton->setCallback( [ this ]()
	{
		requestStatePop();
	} );

	/////////////
	m_container.pack( loadButton );
	m_container.pack( playButton );
	m_container.pack( settingsButton );
	m_container.pack( creditsButton );

	m_container.pack( exitButton );
}

void MainMenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView( window.getDefaultView() );

	window.draw( m_backgroundSprite );
	window.draw( m_container );
}

bool MainMenuState::update( sf::Time delta )
{
	return true;
}

bool MainMenuState::handleEvent( const sf::Event& sfevent )
{
	if ( sfevent.type == sf::Event::KeyPressed && sfevent.key.code == sf::Keyboard::Escape )
		requestStatePush( States::Warning_ETD );

	m_container.handleEvent( sfevent );
	return false;
}