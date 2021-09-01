#include "image_state.hpp"

#include "resource_holder.hpp"

#include "bools.hpp"

#include < SFML/Graphics/RenderWindow.hpp >
#include < SFML/Graphics/View.hpp >

ImageState::ImageState( StateStack& stack, Context context )
	:	State( stack, context )
	,	m_container()
{
	sf::Texture& texture = context.textures->get( Textures::Image );

	m_backgroundSprite.setTexture( texture );

	auto ShowDebugInfoButton = std::make_shared< GUI::LongButton >( *context.fonts, *context.textures );
	ShowDebugInfoButton->setPosition( 960.f, 600.f );
	ShowDebugInfoButton->setText( L"ÎÂÅÐËÅÉ ÎÒËÀÄÊÈ" );
	ShowDebugInfoButton->setCallback( [ this ]()
	{
		Bools::toggleDebugInfoVisibility();
		updateLabels();
	} );

	m_ShowDebugInfoLabel = std::make_shared< GUI::Label >( L"", *context.fonts );
	m_ShowDebugInfoLabel->setPosition( 960.f + 300.f, ShowDebugInfoButton->getPosition().y );
	updateLabels();

	auto backButton = std::make_shared< GUI::Button >( *context.fonts, *context.textures );
	backButton->setPosition( ShowDebugInfoButton->getPosition() + sf::Vector2f( 0.f, 2.f * 70.f + 150.f ) );
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

	m_container.pack( ShowDebugInfoButton );
	m_container.pack( m_ShowDebugInfoLabel );

	m_container.pack( backButton );
}

void ImageState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView( window.getDefaultView() );

	window.draw( m_backgroundSprite );
	window.draw( m_container );
}

bool ImageState::update( sf::Time delta )
{
	return true;
}

bool ImageState::handleEvent( const sf::Event& sfevent )
{
	if ( sfevent.type == sf::Event::KeyPressed && sfevent.key.code == sf::Keyboard::Escape )
	{
		requestStatePop();
		requestStatePush( States::Settings );
	}

	m_container.handleEvent( sfevent );
	return false;
}

void ImageState::updateLabels()
{
	if ( Bools::getDebugInfoVisibility() )
		m_ShowDebugInfoLabel->setText( L"ÂÊËÞ×¨Í" );
	else if ( !Bools::getDebugInfoVisibility() )
		m_ShowDebugInfoLabel->setText( L"ÂÛÊËÞ×ÅÍ" );
}