#include "controls_state.hpp"

#include "bools.hpp"

#include "label.hpp"
#include "button.hpp"
#include "resource_holder.hpp"

#include < SFML/Graphics/RenderWindow.hpp >
#include < SFML/Graphics/View.hpp >

ControlsState::ControlsState( StateStack& stack, Context context )
	:	State( stack, context )
	,	m_container()
{
	sf::Texture& texture = context.textures->get( Textures::Controls );

	m_backgroundSprite.setTexture( texture );

	auto keyBndButton = std::make_shared< GUI::Button >( *context.fonts, *context.textures );
	keyBndButton->setPosition( 960.f, 600.f );
	keyBndButton->setText( L"ÏÐÈÂßÇÊÈ ÊËÀÂÈØ" );
	keyBndButton->setCallback( [ this ]()
	{
		requestStatePop();
		requestStatePush( States::KeyBindings );
	} );

	auto backButton = std::make_shared< GUI::Button >( *context.fonts, *context.textures );
	backButton->setPosition( keyBndButton->getPosition() + sf::Vector2f( 0.f, 2.f * 70.f + 150.f ) );
	backButton->setText( L"ÍÀÇÀÄ" );
	backButton->setCallback( [ this ]()
	{
		requestStatePop();
		requestStatePush( States::Settings );
	} );

	auto versionLabel = std::make_shared< GUI::Label >( Bools::getVersion(), *context.fonts );
	versionLabel->setPosition( sf::Vector2f( 960.f, 1065.f ) );
	versionLabel->setCharacterSize( 18 );
	m_container.pack( versionLabel );

	m_container.pack( keyBndButton );
	m_container.pack( backButton );
}

void ControlsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView( window.getDefaultView() );

	window.draw( m_backgroundSprite );
	window.draw( m_container );
}

bool ControlsState::update( sf::Time delta )
{
	return true;
}

bool ControlsState::handleEvent( const sf::Event& sfevent )
{
	if ( sfevent.type == sf::Event::KeyPressed && sfevent.key.code == sf::Keyboard::Escape )
	{
		requestStatePop();
		requestStatePush( States::Settings );
	}

	m_container.handleEvent( sfevent );
	return false;
}