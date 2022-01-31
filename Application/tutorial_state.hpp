#pragma once

#include "bools.hpp"

#include "state.hpp"
#include "world.hpp"
#include "player.hpp"

#include "dialogue.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class TutorialState : public State
{
public:
	TutorialState( StateStack& stack, Context context );

	virtual void draw();
	virtual bool update( sf::Time delta );
	virtual bool handleEvent( const sf::Event& sfevent );

private:
	World m_world;
	Player& m_player;
};
