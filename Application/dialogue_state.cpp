#pragma warning( disable : 4996 )

#include "dialogue_state.hpp"

#include "bools.hpp"

#include "resource_holder.hpp"
#include "utilities.hpp"

#include < SFML/Graphics/RectangleShape.hpp >
#include < SFML/Graphics/RenderWindow.hpp >
#include < SFML/Graphics/View.hpp >

DialogueState::DialogueState( StateStack& stack, Context context )
	:	State( stack, context )
	,	m_windowSprite()
	,	m_warriorSprite()
	,	m_peasantGirlSprite()
	,	m_container()
	,	m_world( *context.window, *context.fonts )
	,	m_quoteJumpTo( m_world.getStartQuote() )
	,	m_quotes()
	,	m_b_sendToRepeat( false )
{
	sf::Texture& texture   = context.textures->get( Textures::DialogueState );
	sf::Texture& texture_a = context.textures->get( Textures::WarriorF );
	sf::Texture& texture_b = context.textures->get( Textures::PeasantGirlF );

	m_windowSprite.setTexture( texture );
	m_warriorSprite.setTexture( texture_a );
	m_peasantGirlSprite.setTexture( texture_b );

	sf::RenderWindow& window = *getContext().window;
	window.setView( window.getDefaultView() );

	centerOrigin( m_windowSprite );
	centerOrigin( m_warriorSprite );
	centerOrigin( m_peasantGirlSprite );

	//m_warriorSprite.setScale( 1.5f, 1.5f );
	//m_peasantGirlSprite.setScale( 1.5f, 1.5f );

	//m_warriorSprite.setScale( 1.7f, 1.7f );
	//m_peasantGirlSprite.setScale( 1.7f, 1.7f );

	//m_warriorSprite.setScale( 2.3f, 2.3f );
	//m_peasantGirlSprite.setScale( 2.3f, 2.3f );

	m_warriorSprite.setScale( 1.85f, 1.85f );
	m_peasantGirlSprite.setScale( 1.85f, 1.85f );

	m_windowSprite.setPosition(		 window.getView().getCenter().x, window.getView().getCenter().y * 1.5 );
	m_warriorSprite.setPosition(     m_windowSprite.getPosition().x - 700.f, m_windowSprite.getPosition().y - 250.f );
	m_peasantGirlSprite.setPosition( m_windowSprite.getPosition().x + 590.f, m_windowSprite.getPosition().y - 245.f );

	//m_warriorSprite.setPosition(     m_windowSprite.getPosition().x - 720.f, m_windowSprite.getPosition().y - 300.f );
	//m_peasantGirlSprite.setPosition( m_windowSprite.getPosition().x + 610.f, m_windowSprite.getPosition().y - 294.f );

	//m_warriorSprite.setPosition(     m_windowSprite.getPosition().x - 760.f, m_windowSprite.getPosition().y - 200.f );
	//m_peasantGirlSprite.setPosition( m_windowSprite.getPosition().x + 650.f, m_windowSprite.getPosition().y - 196.f );

	//m_warriorSprite.setPosition(     m_windowSprite.getPosition().x - 760.f, m_windowSprite.getPosition().y - 150.f );
	//m_peasantGirlSprite.setPosition( m_windowSprite.getPosition().x + 650.f, m_windowSprite.getPosition().y - 147.f );

	m_quotes = initializeQuotesData();

	Bools::Hero::setInteract( false );
	Dialogue::setConv( false );

	Quotes::ID quoteID = Dialogue::getStartQuote();

	//body///
	
	if ( !Dialogue::getRepeat() )
	{
		switch ( quoteID )
		{
		case Quotes::conversation_D01_quote_PG_00:
		{
			addLabel( m_quotes[ Quotes::conversation_D01_quote_PG_00 ], context );
			addButton( ButtonType::Jump, Quotes::conversation_D01_quote_PG_AA,
					   false, m_windowSprite.getPosition().y + 25.f,
					   m_quotes[ Quotes::conversation_D01_quote_W_A ], context );
			addButtonSecond( ButtonType::Jump, Quotes::conversation_D01_quote_PG_BA,
					   false, m_windowSprite.getPosition().y + 100.f,
					   m_quotes[ Quotes::conversation_D01_quote_W_B ], context );
		break;
		}
		case Quotes::conversation_D01_quote_PG_AA:
		{
			addLabel( m_quotes[ Quotes::conversation_D01_quote_PG_AA ], context );
			addButton( ButtonType::Jump, Quotes::conversation_D01_quote_PG_BA,
					   false, m_windowSprite.getPosition().y + 25.f,
					   m_quotes[ Quotes::conversation_D01_quote_W_AAA_rBA ], context );
			addButtonSecond( ButtonType::Jump, Quotes::conversation_D01_quote_PG_BA,
					   false, m_windowSprite.getPosition().y + 100.f,
					   m_quotes[ Quotes::conversation_D01_quote_W_AAB_rBA ], context );
		break;
		}
		case Quotes::conversation_D01_quote_PG_BA:
		{
			addLabel( m_quotes[ Quotes::conversation_D01_quote_PG_BA ], context );
			addButton( ButtonType::Jump, /*JumpTo:*/ Quotes::conversation_D01_quote_PG_BAAA_ev,
					   false, m_windowSprite.getPosition().y + 25.f,
					   m_quotes[ Quotes::conversation_D01_quote_W_BAA ], context );
			addButtonSecond( ButtonType::End, /*JumpTo:*/ Quotes::conversation_D02_quote_PG_00_rt,
					   true, m_windowSprite.getPosition().y + 100.f,
					   m_quotes[ Quotes::conversation_D01_quote_W_BAB_q ], context );
		break;
		}
		case Quotes::conversation_D01_quote_PG_BAAA_ev:
		{
			addLabel( m_quotes[ Quotes::conversation_D01_quote_PG_BAAA_ev ], context );
			addButtonSecond( ButtonType::Event, Quotes::conversation_D01_quote_PG_00,
					   false, m_windowSprite.getPosition().y + 25.f,
					   m_quotes[ Quotes::Button_Quote ], context );
			break;
		}

		default:
			errorOccured( context );
		}
	}
	else if ( Dialogue::getRepeat() )
	{
		switch ( quoteID )
		{
		case Quotes::conversation_D02_quote_PG_00_rt:
		{
			addLabel( m_quotes[ Quotes::conversation_D02_quote_PG_00_rt ], context );
			addButton( ButtonType::Jump, Quotes::conversation_D02_quote_PG_AA_ev,
					   false, m_windowSprite.getPosition().y + 25.f,
					   m_quotes[ Quotes::conversation_D02_quote_W_A ], context );
			addButtonSecond( ButtonType::Jump, Quotes::conversation_D02_quote_PG_BA_ev,
					   true, m_windowSprite.getPosition().y + 100.f,
					   m_quotes[ Quotes::conversation_D02_quote_W_B ], context );
		break;
		}
		case Quotes::conversation_D02_quote_PG_AA_ev:
		{
			addLabel( m_quotes[ Quotes::conversation_D02_quote_PG_AA_ev ], context );
			addButtonSecond( ButtonType::Event, Quotes::conversation_D01_quote_PG_00,
					   false, m_windowSprite.getPosition().y + 25.f,
					   m_quotes[ Quotes::Button_Quote ], context );
		break;
		}
		case Quotes::conversation_D02_quote_PG_BA_ev:
		{
			addLabel( m_quotes[ Quotes::conversation_D02_quote_PG_BA_ev ], context );
			addButtonSecond( ButtonType::Event, Quotes::conversation_D01_quote_PG_00,
					   false, m_windowSprite.getPosition().y + 25.f,
					   m_quotes[ Quotes::Button_Quote ], context );
		break;
		}
		default:
			errorOccured( context );
		break;
		}
	}
	
	///body//
}

void DialogueState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView( window.getDefaultView() );

	window.draw( m_windowSprite );
	window.draw( m_warriorSprite );
	window.draw( m_peasantGirlSprite );

	window.draw( m_container );
}

bool DialogueState::update( sf::Time delta )
{
	Bools::Time::increaseGLobalTimer( delta );

	return false;
}

bool DialogueState::handleEvent( const sf::Event& sfevent )
{
	if ( sfevent.type == sf::Event::KeyPressed && sfevent.key.code == sf::Keyboard::Escape )
		requestStatePush( States::PauseMenu );
	m_container.handleEvent( sfevent );
	return false;
}

void DialogueState::addLabel( const std::wstring& text, Context context )
{
	auto genericLabel = std::make_shared< GUI::Label >( text, *context.fonts );
	genericLabel->setPosition( m_windowSprite.getPosition().x, m_windowSprite.getPosition().y - 110.f );

	m_container.pack( genericLabel );
}

void DialogueState::addButton( ButtonType type, Quotes::ID jumpto, bool sendToRepeat, float pillar, const std::wstring& text, Context context )
{
	auto genericButton = std::make_shared< GUI::DialogueButton >( *context.fonts, *context.textures );
	genericButton->setPosition( m_windowSprite.getPosition().x, pillar );
	genericButton->setText( text );

	m_quoteJumpTo = jumpto;
	m_b_sendToRepeat = sendToRepeat;

	switch ( type )
	{
	case Forward:
	{
		genericButton->setCallback( [ this ]()
		{
			requestStatePop();
			requestStatePush( States::Dialogue );
		} );
	break;
	}
	case Jump:
	{
		genericButton->setCallback( [ this ]()
		{
			Dialogue::setStartQuote( m_quoteJumpTo );

			requestStatePop();
			requestStatePush( States::Dialogue );
		} );
	break;
	}
	case End:
	{
		genericButton->setCallback( [ this ]()
		{
			requestStatePop();
		} );
	break;
	}
	case Event:
	{
		genericButton->setCallback( [ this ]()
		{
			Dialogue::setStartQuote( m_quoteJumpToSecond );

			requestStateClear();
			requestStatePush( States::Flash );
		} );
	break;
	}
	}

	m_container.pack( genericButton );
}

void DialogueState::addButtonSecond( ButtonType type, Quotes::ID jumpto, bool sendToRepeat, float pillar, const std::wstring& text, Context context )
{
	auto genericButton = std::make_shared< GUI::DialogueButton >( *context.fonts, *context.textures );
	genericButton->setPosition( m_windowSprite.getPosition().x, pillar );
	genericButton->setText( text );

	m_quoteJumpToSecond = jumpto;
	m_b_sendToRepeat = sendToRepeat;

	switch ( type )
	{
	case Forward:
	{
		genericButton->setCallback( [ this ]()
		{
			requestStatePop();
			requestStatePush( States::Dialogue );
		} );
	break;
	}
	case Jump:
	{
		genericButton->setCallback( [ this ] ()
		{
			Dialogue::setStartQuote( m_quoteJumpToSecond );
			Dialogue::setRepeat( m_b_sendToRepeat );

			requestStatePop();
			requestStatePush( States::Dialogue );
		} );
	break;
	}
	case End:
	{
		genericButton->setCallback( [ this ]()
		{
			Dialogue::setStartQuote( m_quoteJumpToSecond );
			Dialogue::setRepeat( m_b_sendToRepeat );

			requestStatePop();
		} );
	break;
	}
	case Event:
	{
		genericButton->setCallback( [ this ]()
		{
			Dialogue::setStartQuote( m_quoteJumpToSecond );
			Dialogue::setRepeat( m_b_sendToRepeat );

			requestStateClear();
			requestStatePush( States::Flash );
		} );
	break;
	}
	}

	m_container.pack( genericButton );
}

void DialogueState::errorOccured( Context context )
{
	addLabel( m_quotes[ Quotes::Empty_Quote ], context );
	addButton( ButtonType::End, Quotes::Empty_Quote,
			   false, m_windowSprite.getPosition().y,
			   m_quotes[ Quotes::Button_Quote ], context );
}