#pragma once

#include "resource_holder.hpp"
#include "resource_identify.hpp"
#include "player.hpp"
#include "state_stack.hpp"

#include "bools.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Application
{
public:
    Application( int screenX, int screenY );

    void run();

private:
    void processInput();
    void update( sf::Time delta );
    void render();

    void updateCounters( sf::Time delta );
    void updateTime( sf::Time delta );
    void registerStates();

private:
    static const sf::Time TimePerFrame;

    sf::RenderWindow m_renderWindow;

    TextureHolder m_textures;
    FontHolder m_fonts;

    Player m_player;

    StateStack m_stateStack;

    sf::Text m_debugText;
    sf::Time m_debugUpdateTime;
    std::size_t m_debugFramesCounter;

    sf::Text m_timeText;
    sf::Time m_timeUpdateTime;
};
