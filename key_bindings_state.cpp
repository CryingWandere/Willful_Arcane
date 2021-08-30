#include "key_bindings_state.hpp"

#include "bools.hpp"

#include "resource_holder.hpp"
#include "utilities.hpp"

#include < SFML/Graphics/RenderWindow.hpp >

KeyBindingsState::KeyBindingsState( StateStack& stack, Context context )
	:	State( stack, context )
	,	m_container()
{
	sf::Texture& texture = context.textures->get( Textures::Controls );

	m_backgroundSprite.setTexture( texture );
	
	addButton( Player::MoveForward, 535.f, L"¬¬≈–’", context );
	addButton( Player::MoveBack, 535.f + 70.f, L"¬Õ»«", context );
	addButton( Player::MoveLeft, 535.f + 140.f, L"¬À≈¬Œ", context );
	addButton( Player::MoveRight, 535.f + 210.f, L"¬œ–¿¬Œ", context );
	addButton( Player::Attack, 535.f + 280.f, L"¿“¿ ¿", context );
	addButton( Player::Interact, 535.f + 350.f, L"¬«¿»ÃŒƒ≈…—“¬»≈", context );
	addButton( Player::ChangeScale, 535.f + 420.f, L"»«Ã≈Õ≈Õ»≈ Ã¿—ÿ“¿¡¿", context );

	updateLabels();

	auto backButton = std::make_shared< GUI::Button >( *context.fonts, *context.textures );
	backButton->setPosition( 960.f, 100.f );
	backButton->setText( L"Õ¿«¿ƒ" );
	backButton->setCallback( [ this ]()
	{
		requestStatePop();
		requestStatePush( States::Controls );
	} );

	auto versionLabel = std::make_shared< GUI::Label >( Bools::getVersion(), *context.fonts );
	versionLabel->setPosition( sf::Vector2f( 960.f, 1065.f ) );
	versionLabel->setCharacterSize( 18 );
	m_container.pack( versionLabel );

	m_container.pack( backButton );
}

void KeyBindingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw( m_backgroundSprite );
	window.draw( m_container );
}

bool KeyBindingsState::update( sf::Time delta )
{
	return true;
}

bool KeyBindingsState::handleEvent( const sf::Event& sfevent )
{
	bool isKeyBinding = false;

	for ( std::size_t action = 0; action < Player::TotalActions; action++ )
	{
		if ( m_bindingButtons[ action ]->isActive() )
		{
			isKeyBinding = true;

			if ( sfevent.type == sf::Event::KeyPressed )
			{
				if ( sfevent.key.code == sf::Keyboard::Escape  ||
					 sfevent.key.code == sf::Keyboard::Pause   ||
					 sfevent.key.code == sf::Keyboard::LSystem ||
					 sfevent.key.code == sf::Keyboard::RSystem    )
					requestStatePush( States::Alert_WKS );
				else
					getContext().player->bindKey( static_cast< Player::Action >( action ), sfevent.key.code );
				m_bindingButtons[ action ]->deactivate();
			}
			break;
		}
	}

	if ( isKeyBinding )
		updateLabels();
	else
		{
			if ( sfevent.type == sf::Event::KeyPressed && sfevent.key.code == sf::Keyboard::Escape )
			{
				requestStatePop();
				requestStatePush( States::Controls );
			}

			m_container.handleEvent( sfevent );
		}

	return false;
}

void KeyBindingsState::updateLabels()
{
	Player& player = *getContext().player;

	for ( std::size_t cntr = 0; cntr < Player::TotalActions; cntr++ )
	{
		sf::Keyboard::Key key = player.getBoundKey( static_cast< Player::Action >( cntr ) );
		m_bindingLabels[ cntr ]->setText( toString( key ) );
	}
}

void KeyBindingsState::addButton( Player::Action action, float pillar, const std::wstring& text, Context context )
{
	m_bindingButtons[ action ] = std::make_shared< GUI::LongButton >( *context.fonts, *context.textures );
	m_bindingButtons[ action ]->setPosition( 960.f, pillar );
	m_bindingButtons[ action ]->setText( text );
	m_bindingButtons[ action ]->setToggle( true );

	m_bindingLabels[ action ] = std::make_shared< GUI::UTF8Label >( "", *context.fonts );
	m_bindingLabels[ action ]->setPosition( 960.f + 300.f, pillar );

	m_container.pack( m_bindingButtons[ action ] );
	m_container.pack( m_bindingLabels[ action ] );
}