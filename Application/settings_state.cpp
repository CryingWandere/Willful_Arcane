#include "settings_state.hpp"

#include "bools.hpp"

#include "label.hpp"
#include "button.hpp"
#include "resource_holder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

SettingsState::SettingsState( StateStack& stack, Context context )
	:	State( stack, context )
	,	m_container()
{
	sf::Texture& texture = context.textures->get( Textures::SettingsScreen );

	m_backgroundSprite.setTexture( texture );

	auto videoButton = std::make_shared< GUI::Button >( *context.fonts, *context.textures );
	videoButton->setPosition( 960.f, 600.f );
	videoButton->setText( L"ИЗОБРАЖЕНИЕ" );
	videoButton->setCallback( [ this ]()
	{
		requestStatePop();
		requestStatePush( States::Image );
	} );

	auto audioButton = std::make_shared< GUI::Button >( *context.fonts, *context.textures );
	audioButton->setPosition( videoButton->getPosition() + sf::Vector2f( 0.f, 70.f ) );
	audioButton->setText( L"ЗВУК" );
	audioButton->setCallback( [ this ]()
	{
	} );

	auto controlsButton = std::make_shared< GUI::Button >( *context.fonts, *context.textures );
	controlsButton->setPosition( audioButton->getPosition() + sf::Vector2f( 0.f, 70.f ) );
	controlsButton->setText( L"УПРАВЛЕНИЕ" );
	controlsButton->setCallback( [ this ]()
	{
		requestStatePop();
		requestStatePush( States::Controls );
	} );

	auto backButton = std::make_shared< GUI::Button >( *context.fonts, *context.textures );
	backButton->setPosition( controlsButton->getPosition() + sf::Vector2f( 0.f, 150.f ) );
	backButton->setText( L"НАЗАД" );
	backButton->setCallback( [ this ]()
	{
		requestStatePop();
	} );

	auto versionLabel = std::make_shared< GUI::Label >( Bools::getVersion(), *context.fonts );
	versionLabel->setPosition( sf::Vector2f( 960.f, 1065.f ) );
	versionLabel->setCharacterSize( 18 );
	m_container.pack( versionLabel );

	/////////////
	m_container.pack( videoButton );
	m_container.pack( audioButton );
	m_container.pack( controlsButton );
	m_container.pack( backButton );
}

void SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView( window.getDefaultView() );

	window.draw( m_backgroundSprite );
	window.draw( m_container );
}

bool SettingsState::update( sf::Time delta )
{
	return true;
}

bool SettingsState::handleEvent( const sf::Event& sfevent )
{
	if ( sfevent.type == sf::Event::KeyPressed && sfevent.key.code == sf::Keyboard::Escape )
	{
		requestStatePop();
	}

	m_container.handleEvent( sfevent );
	return false;
}
