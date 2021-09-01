#include "quote_identify.hpp"

void Quotes::setCurrentQuote( Quotes::ID quote )
{
	currentQuote = quote;
}

Quotes::ID Quotes::getCurrentQuote()
{
	return currentQuote;
}