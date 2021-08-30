#pragma warning( disable : 4996 )

#include "warning_etd_state.hpp"

#include "resource_holder.hpp"
#include "short_button.hpp"
#include "label.hpp"
#include "utilities.hpp"

#include < SFML/Graphics/RenderWindow.hpp >
#include < SFML/Graphics/View.hpp >

WarningState::WarningState( StateStack& stack, Context context )
	:	State( stack, context )
	,	m_windowSprite()
	,	m_container()
{
	sf::Texture& texture = context.textures->get( Textures::WarningState );

	m_windowSprite.setTexture( texture );

	sf::RenderWindow& window = *getContext().window;
	window.setView( window.getDefaultView() );

	centerOrigin( m_windowSprite );
	m_windowSprite.setPosition( window.getView().getCenter().x, window.getView().getCenter().y );

	auto yesButton = std::make_shared< GUI::ShortButton >( *context.fonts, *context.textures );
	yesButton->setPosition( m_windowSprite.getPosition().x - 140.f, m_windowSprite.getPosition().y + 105.f );
	yesButton->setText( L"ÄÀ" );
	yesButton->setCallback( [this]()
	{
		requestStateClear();
	} );

	auto noButton = std::make_shared< GUI::ShortButton >( *context.fonts, *context.textures );
	noButton->setPosition( m_windowSprite.getPosition().x + 140.f, m_windowSprite.getPosition().y + 105.f );
	noButton->setText( L"ÍÅÒ" );
	noButton->setCallback( [this]()
	{
		requestStatePop();
	} );

	auto infoLabel = std::make_shared< GUI::Label >( L"ÂÛÉÒÈ ÍÀ ÐÀÁÎ×ÈÉ ÑÒÎË?", *context.fonts );
	infoLabel->setPosition( m_windowSprite.getPosition().x, m_windowSprite.getPosition().y - 95.f );

	m_container.pack( infoLabel );

	m_container.pack( yesButton );
	m_container.pack( noButton );
}

void WarningState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView( window.getDefaultView() );

	window.draw( m_windowSprite );
	window.draw( m_container );
}

bool WarningState::update( sf::Time delta )
{
	return false;
}

bool WarningState::handleEvent( const sf::Event& sfevent )
{
	m_container.handleEvent( sfevent );
	return false;
}