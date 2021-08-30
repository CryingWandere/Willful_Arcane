#pragma warning( disable : 4996 )

#include "alert_wks_state.hpp"

#include "resource_holder.hpp"
#include "short_button.hpp"
#include "label.hpp"
#include "utilities.hpp"

#include < SFML/Graphics/RenderWindow.hpp >
#include < SFML/Graphics/View.hpp >

AlertState::AlertState( StateStack& stack, Context context )
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

	auto okButton = std::make_shared< GUI::ShortButton >( *context.fonts, *context.textures );
	okButton->setPosition( m_windowSprite.getPosition().x, m_windowSprite.getPosition().y + 105.f );
	okButton->setText( L"ÎÊ" );
	okButton->setCallback( [this]()
	{
		requestStatePop();
	} );

	auto infoLabel = std::make_shared< GUI::Label >( L"ÍÅËÜÇß ÍÀÇÍÀ×ÈÒÜ\n ÄÀÍÍÓÞ ÊËÀÂÈØÓ", *context.fonts );
	infoLabel->setPosition( m_windowSprite.getPosition().x, m_windowSprite.getPosition().y - 80.f );

	m_container.pack( infoLabel );

	m_container.pack( okButton );
}

void AlertState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView( window.getDefaultView() );

	window.draw( m_windowSprite );
	window.draw( m_container );
}

bool AlertState::update( sf::Time delta )
{
	return false;
}

bool AlertState::handleEvent( const sf::Event& sfevent )
{
	m_container.handleEvent( sfevent );
	return false;
}