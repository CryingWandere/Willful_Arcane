#pragma warning( disable : 4996 )

#include "application.hpp"

#include "state.hpp"
#include "state_identify.hpp"

#include "bools.hpp"

////////////////////////
#include "title_state.hpp"
#include "mainMenu_state.hpp"
#include "settings_state.hpp"
	#include "controls_state.hpp"
		#include "key_bindings_state.hpp"
	#include "image_state.hpp"
#include "credits_state.hpp"

#include "dialogue_state.hpp"

#include "pauseMenu_state.hpp"

#include "warning_etd_state.hpp"

#include "alert_wks_state.hpp"

#include "tutorial_state.hpp"
#include "white_state.hpp"
#include "forest_state.hpp"

#include "final_state.hpp"
////////////////////////

const sf::Time Application::TimePerFrame = sf::seconds( 1.f / 300.f );

Application::Application( int screenX, int screenY )
	:	m_renderWindow( sf::VideoMode( screenX, screenY ), "Willful Arcane [Alpha]", sf::Style::Fullscreen | sf::Style::Close )
	,	m_textures()
	,	m_fonts()
	,	m_player()
	,	m_stateStack( State::Context( m_renderWindow, m_textures, m_fonts, m_player ) )
	,	m_debugText()
	,	m_debugUpdateTime()
	,	m_debugFramesCounter( 0 )
	,	m_timeText()
	,	m_timeUpdateTime()
{
	m_renderWindow.setKeyRepeatEnabled( false );
	m_renderWindow.setMouseCursorVisible( false );

	//Òåêñòóðû

	m_fonts.load( Fonts::RetroGaming, "Fonts/RetroGaming.ttf" );
	//Ãëàâíûé çàäíèê
	m_textures.load( Textures::TitleScreen, "Textures/main_menu.jpg" );
	//Çàäíèêè
	m_textures.load( Textures::MainMenuScreen, "Textures/main_menu.jpg" );
	m_textures.load( Textures::SettingsScreen, "Textures/settings.jpg" );
		m_textures.load( Textures::Controls, "Textures/controls.jpg" );
		m_textures.load( Textures::Image, "Textures/image.jpg" );
	//Âñïëûâàþùèå îêíà
	m_textures.load( Textures::WarningState, "Textures/GUI/warning_state.png" );
	m_textures.load( Textures::DialogueState, "Textures/GUI/dialogue_state.png" );
	//Êíîïêè
	m_textures.load( Textures::LockedButton, "Textures/GUI/button_locked.png" );
	m_textures.load( Textures::DefaultButton, "Textures/GUI/button_default.png" );
	m_textures.load( Textures::SelectedButton, "Textures/GUI/button_selected.png" );
	m_textures.load( Textures::PressedButton, "Textures/GUI/button_pressed.png" );

	m_textures.load( Textures::LockedShortButton, "Textures/GUI/shortbutton_locked.png" );
	m_textures.load( Textures::DefaultShortButton, "Textures/GUI/shortbutton_default.png" );
	m_textures.load( Textures::SelectedShortButton, "Textures/GUI/shortbutton_selected.png" );
	m_textures.load( Textures::PressedShortButton, "Textures/GUI/shortbutton_pressed.png" );

	m_textures.load( Textures::DefaultLongButton, "Textures/GUI/longbutton_default.png" );
	m_textures.load( Textures::SelectedLongButton, "Textures/GUI/longbutton_selected.png" );
	m_textures.load( Textures::PressedLongButton, "Textures/GUI/longbutton_pressed.png" );
	//Âñïûøêà
	m_textures.load( Textures::Flash01, "Textures/level_bgs/flash01.jpg" );
	//Àðòû ñ ïåðñîíàæàìè äëÿ äèàëîãîâûõ îêîí
	m_textures.load( Textures::WarriorF, "Textures/heroes_fgs/warrior/warrior.png" );
	m_textures.load( Textures::PeasantGirlF, "Textures/npcs_fgs/peasant_girl.png" );

	////////////////////////
	m_debugText.setFont( m_fonts.get( Fonts::RetroGaming ) );
	m_debugText.setPosition( 5.f, 5.f );
	m_debugText.setCharacterSize( 18 );
	m_debugText.setColor( sf::Color::Color( 0xdd, 0xdd, 0xdd, 250 ) );
	m_debugText.setOutlineColor( sf::Color::Color( 0x00, 0x00, 0x00, 250 ) );
	m_debugText.setOutlineThickness( 1 );

	m_timeText.setFont( m_fonts.get( Fonts::RetroGaming ) );
	m_timeText.setPosition( 1776.f, 5.f );
	m_timeText.setCharacterSize( 18 );
	m_timeText.setColor( sf::Color::Color( 0xdd, 0xdd, 0xdd, 250 ) );
	m_timeText.setOutlineColor( sf::Color::Color( 0x00, 0x00, 0x00, 250 ) );
	m_timeText.setOutlineThickness( 1 );

	registerStates();
	m_stateStack.pushState( States::Title ); //debug
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while ( m_renderWindow.isOpen() )
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;

		while ( timeSinceLastUpdate > TimePerFrame )
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update( TimePerFrame );

			if ( m_stateStack.isEmpty() )
				m_renderWindow.close();
		}

		updateCounters( delta );
		updateTime( delta );

		render();
	}
}

void Application::processInput()
{
	sf::Event main_event;

	while ( m_renderWindow.pollEvent( main_event ) )
	{
		m_stateStack.handleEvent( main_event );

		if ( main_event.type == sf::Event::Closed )
			m_renderWindow.close();
	}
}

void Application::update( sf::Time delta )
{
	if ( m_renderWindow.hasFocus() )
		m_stateStack.update( delta );
}

void Application::render()
{
	m_renderWindow.clear();

	m_stateStack.draw();

	m_renderWindow.setView( m_renderWindow.getDefaultView() );

	if( Bools::getDebugInfoVisibility() )
	{
		m_renderWindow.draw( m_debugText );
		m_renderWindow.draw( m_timeText );
	}

	m_renderWindow.display();
}

void Application::updateCounters( sf::Time delta )
{
	m_debugUpdateTime += delta;
	m_debugFramesCounter += 1;

	if ( m_debugUpdateTime >= sf::seconds( 1.0f ) )
	{
		m_debugText.setString(
		"FPS: " + std::to_string( m_debugFramesCounter ) + "\n" +
		"TPU: " + std::to_string( m_debugUpdateTime.asMicroseconds() / m_debugFramesCounter ) + " us" );

		m_debugUpdateTime -= sf::seconds( 1.0f );
		m_debugFramesCounter = 0;
	}
}

void Application::updateTime( sf::Time delta )
{
	m_timeUpdateTime += delta;

	if ( m_timeUpdateTime >= sf::milliseconds( 1.f ) )
	{
		std::string temp =			std::to_string( static_cast< int >(			  trunc( Bools::Time::getGlobalTimer().asSeconds()   / 60  ) ) ) + ":";
					 if ( ( static_cast< int >( Bools::Time::getGlobalTimer().asSeconds() ) % 60 ) < 10 )
						 temp += "0" + std::to_string( static_cast< int >( static_cast< int >( Bools::Time::getGlobalTimer().asSeconds() ) % 60    ) ) + ".";
					 else
						 temp +=		std::to_string( static_cast< int >( static_cast< int >( Bools::Time::getGlobalTimer().asSeconds() ) % 60	 ) ) + ".";
					 if		 ( ( static_cast< int >( Bools::Time::getGlobalTimer().asMilliseconds() ) % 1000 ) < 10    )
							 temp += "00" + std::to_string( static_cast< int >( static_cast< int >( Bools::Time::getGlobalTimer().asMilliseconds() ) % 1000 ) );
					 else if ( ( static_cast< int >( Bools::Time::getGlobalTimer().asMilliseconds() ) % 1000 ) < 100   )
					 		 temp +=  "0" + std::to_string( static_cast< int >( static_cast< int >( Bools::Time::getGlobalTimer().asMilliseconds() ) % 1000 ) );
					 else
							 temp +=         std::to_string( static_cast< int >( static_cast< int >( Bools::Time::getGlobalTimer().asMilliseconds() ) % 1000 ) );

		m_timeText.setString( "WT: " + temp );

		m_timeUpdateTime -= sf::milliseconds( 1.f );
	}
}

void Application::registerStates()
{
	m_stateStack.registerState< TitleState >( States::Title );
	m_stateStack.registerState< MainMenuState >( States::MainMenu );
	m_stateStack.registerState< PauseMenuState >( States::PauseMenu );

	m_stateStack.registerState< SettingsState >( States::Settings );
		m_stateStack.registerState< ControlsState >( States::Controls );
			m_stateStack.registerState< KeyBindingsState >( States::KeyBindings );
		m_stateStack.registerState< ImageState >( States::Image );
	m_stateStack.registerState< CreditsState >( States::Credits );
	
	m_stateStack.registerState< DialogueState >( States::Dialogue );

	m_stateStack.registerState< WarningState >( States::Warning_ETD );

	m_stateStack.registerState< AlertState >( States::Alert_WKS );
	
	m_stateStack.registerState< TutorialState >( States::Tutorial );
	m_stateStack.registerState< WhiteState >( States::Flash );
	m_stateStack.registerState< ForestState >( States::Forest );

	m_stateStack.registerState< FinalState >( States::Final );
}
