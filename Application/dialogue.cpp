#include "dialogue.hpp"

void Dialogue::setConv( bool start )
{
	isActive = start;
}

bool Dialogue::getConv()
{
	return isActive;
}

void Dialogue::setStartQuote( Quotes::ID start )
{
	startQuote = start;
}

Quotes::ID Dialogue::getStartQuote()
{
	return startQuote;
}

void Dialogue::setRepeat( bool start )
{
	isRepeated = start;
}

bool Dialogue::getRepeat()
{
	return isRepeated;
}