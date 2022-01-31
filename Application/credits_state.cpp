#include "credits_state.hpp"

#include "label.hpp"
#include "button.hpp"
#include "resource_holder.hpp"
#include "color_identify.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

CreditsState::CreditsState( StateStack& stack, Context context )
    :	State( stack, context )
    ,	m_container()
{
    auto programmer = std::make_shared< GUI::Label >(
        L"Ведущий разработчик, Технический директор, Программист, Геймдизайнер",
        *context.fonts );
    programmer->setColor( getColor( Colors::Font_muted ) );
    programmer->setPosition( sf::Vector2f( 960.f, 140.f ) );
    auto programmer_b = std::make_shared< GUI::Label >(
        L"Художник текстур, Дизайн уровней, Дизайн интерфейса",
        *context.fonts);
    programmer_b->setColor( getColor( Colors::Font_muted ) );
    programmer_b->setPosition( programmer->getPosition() + sf::Vector2f( 0.f, 40.f ) );

    auto fullname1 = std::make_shared< GUI::Label >( L"Фёдор Агафонов", *context.fonts );
    fullname1->setPosition( programmer_b->getPosition() + sf::Vector2f( 0.f, 70.f ) );

    auto HR = std::make_shared< GUI::Label >(
        L"HR-менеджер, Сценарист, Нарративный директор, Композитор",
        *context.fonts );
    HR->setColor( getColor( Colors::Font_muted ) );
    HR->setPosition( fullname1->getPosition() + sf::Vector2f( 0.f, 120.f ) );

    auto fullname2 = std::make_shared< GUI::Label >( L"Вано Папашвили", *context.fonts );
    fullname2->setPosition( HR->getPosition() + sf::Vector2f( 0.f, 70.f ) );

    auto artist = std::make_shared< GUI::Label >(
        L"Арт-директор, Ведущий художник персонажей, Концепт художник, Художник",
        *context.fonts );
    artist->setColor( getColor( Colors::Font_muted ) );
    artist->setPosition( fullname2->getPosition() + sf::Vector2f( 0.f, 120.f ) );

    auto fullname3 = std::make_shared< GUI::Label >( L"Иван Рогов", *context.fonts );
    fullname3->setPosition( artist->getPosition() + sf::Vector2f( 0.f, 70.f ) );

    auto web = std::make_shared< GUI::Label >(
        L"Веб-разработчик",
        *context.fonts );
    web->setColor( getColor( Colors::Font_muted ) );
    web->setPosition( fullname3->getPosition() + sf::Vector2f( 0.f, 120.f ) );

    auto fullname4 = std::make_shared< GUI::Label >( L"Андрей Белканов", *context.fonts );
    fullname4->setPosition( web->getPosition() + sf::Vector2f( 0.f, 70.f ) );

    auto backButton = std::make_shared< GUI::Button >( *context.fonts, *context.textures );
    backButton->setPosition( 960.f, 980.f );
    backButton->setText( L"НАЗАД" );
    backButton->setCallback( [ this ]()
    {
        requestStatePop();
        requestStatePush( States::MainMenu );
    } );

    m_container.pack( programmer );
    m_container.pack( programmer_b );
    m_container.pack( fullname1 );
    m_container.pack( HR );
    m_container.pack( fullname2 );
    m_container.pack( artist );
    m_container.pack( fullname3 );
    m_container.pack( web );
    m_container.pack( fullname4 );

    m_container.pack( backButton );
}

void CreditsState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView( window.getDefaultView() );

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor( getColor( Colors::Menu_background ) );
    backgroundShape.setSize( window.getView().getSize() );

    window.draw( backgroundShape );
    window.draw( m_container );
}

bool CreditsState::update( sf::Time delta )
{
    return true;
}

bool CreditsState::handleEvent( const sf::Event& sfevent )
{
    if ( sfevent.type == sf::Event::KeyPressed && sfevent.key.code == sf::Keyboard::Escape )
    {
        requestStatePop();
        requestStatePush( States::MainMenu );
    }

    m_container.handleEvent( sfevent );
    return false;
}
