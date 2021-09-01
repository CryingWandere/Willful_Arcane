#include "bools.hpp"

void Bools::toggleDebugInfoVisibility()
{
	isDebugInfoVisible = !isDebugInfoVisible;
}

void Bools::setDebugInfoVisibility( bool internal_isDebugInfoVisible )
{
	isDebugInfoVisible = internal_isDebugInfoVisible;
}

bool Bools::getDebugInfoVisibility()
{
	return isDebugInfoVisible;
}

std::wstring Bools::getVersion()
{
	return version;
}

//Time//
void Bools::Time::setGlobalTimer( sf::Time timer )
{
	globalTimer = timer;
}

void Bools::Time::increaseGLobalTimer( sf::Time delta )
{
	globalTimer += delta;
}

sf::Time Bools::Time::getGlobalTimer()
{
	return globalTimer;
}

//Hero//
void Bools::Hero::setInteract( bool internal_interact )
{
	interact = internal_interact;
}

bool Bools::Hero::getInteract()
{
	return interact;
}
