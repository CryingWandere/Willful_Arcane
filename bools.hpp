#pragma once

#include < string >

#include < SFML/System/Time.hpp >

namespace Bools
{
    void toggleDebugInfoVisibility();
    void setDebugInfoVisibility( bool internal_isDebugInfoVisible );
    bool getDebugInfoVisibility();

    std::wstring getVersion();

    namespace Hero
    {
        void setInteract( bool internal_interact );
        bool getInteract();
    }

    namespace Time
    {
        void setGlobalTimer( sf::Time timer );
        void increaseGLobalTimer( sf::Time delta );
        sf::Time getGlobalTimer();
    }
}

namespace
{
    std::wstring version = L"CV: Demo 1.7.2 Final   Engine: Aegis 2.4.4   GUI: Aegis GUI 1.2.2";
    bool isDebugInfoVisible = true;

    //Time
         sf::Time globalTimer = sf::Time::Zero;

    //Hero
        bool interact = false;
}