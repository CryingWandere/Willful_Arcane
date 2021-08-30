#pragma once

// 00 - first quote
// r<quote_code> - return to quote <quote_code>
// q - end conversation
// rt - second conversation
// ev - start event

// PG  - peasant girl
// W   - warrior

namespace Quotes
{
	enum ID
	{
		Empty_Quote,

		conversation_D01_quote_PG_00,
		conversation_D01_quote_W_A,
		conversation_D01_quote_W_B,
		conversation_D01_quote_PG_AA,
		conversation_D01_quote_PG_BA,
		conversation_D01_quote_W_AAA_rBA,
		conversation_D01_quote_W_AAB_rBA,
		conversation_D01_quote_W_BAA,
		conversation_D01_quote_W_BAB_q,
		conversation_D01_quote_PG_BAAA_ev,
		conversation_D02_quote_PG_00_rt,
		conversation_D02_quote_W_A,
		conversation_D02_quote_W_B,
		conversation_D02_quote_PG_AA_ev,
		conversation_D02_quote_PG_BA_ev,

		Button_Quote,

		AllQuotes
	};

	void setCurrentQuote( Quotes::ID quote );
	ID getCurrentQuote();
}

namespace
{
	Quotes::ID currentQuote = Quotes::conversation_D01_quote_PG_00;
}