#pragma once

#include "quotes_storage.hpp"

namespace Dialogue
{
	void setConv( bool start );
	bool getConv();

	void setRepeat( bool start );
	bool getRepeat();

	void setStartQuote( Quotes::ID start );
	Quotes::ID getStartQuote();
};

namespace
{
	Quotes::ID startQuote = Quotes::conversation_D01_quote_PG_00;
	bool isActive = false;
	bool isRepeated = false;
}