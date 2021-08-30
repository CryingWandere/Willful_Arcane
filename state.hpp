#pragma once

#include "state_identify.hpp"
#include "resource_identify.hpp"

#include < SFML/System/Time.hpp >
#include < SFML/Window/Event.hpp >

#include < memory >

//Forward declaration
namespace sf
{
	class RenderWindow;
}

class StateStack;
class Player;

//

class State
{
public:
	typedef std::unique_ptr< State > Pointer;

	struct Context
	{
		Context( sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player );

		sf::RenderWindow* window;
		TextureHolder* textures;
		FontHolder* fonts;
		Player* player;
	};

public:
	State( StateStack& stack, Context context );
	virtual ~State();

	virtual void draw() = 0;
	virtual bool update( sf::Time delta ) = 0;
	virtual bool handleEvent( const sf::Event& sfevent ) = 0;

protected:
	void requestStatePush( States::ID stateID );
	void requestStatePop();
	void requestStateClear();

	Context getContext() const;

private:
	StateStack* m_stack;

	Context m_context;
};