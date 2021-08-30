#include "quotes_storage.hpp"

// 00 - first quote
// r<quote_code> - return to quote <quote_code>
// q - end conversation
// rt - second conversation
// ev - start event

// PG  - peasant girl
// W   - warrior

std::vector< std::wstring > initializeQuotesData()
{
	std::vector< std::wstring > data( Quotes::AllQuotes );

	data[ Quotes::Empty_Quote ]										= L"???missing_quote???";

	data[ Quotes::conversation_D01_quote_PG_00 ]					= L"Здравствуй, Ильгиз, одиноко идущий по полю.\nГадаю, что ведёт тебя по нашему мирному краю?";
	data[ Quotes::conversation_D01_quote_W_A ]						= L"Здравствуй, девушка, а откуда ты знаешь моё имя?";
	data[ Quotes::conversation_D01_quote_W_B ]						= L"А я гадаю, чего ты тут стоишь, да меня дожидаешься...";
	data[ Quotes::conversation_D01_quote_PG_AA ]					= L"Я немало о тебе знаю, и идешь ты куда, и зачем,\nдаже когда окажешься в той или иной точке своего пути.\nВот решила здесь тебя встретить, на лицо твоё посмотреть.";
	data[ Quotes::conversation_D01_quote_PG_BA ]					= L"Все гадают, а ещё гадают зачем идут,\nкуда, когда придут, всё это пустое, не находишь?\nЭти загадки мало к чему приведут, уж точно не к ответам.";
	data[ Quotes::conversation_D01_quote_W_AAA_rBA ]				= L"А я на твоё тогда погляжу, знать бы ещё, на кой я тебе сдался.";
	data[ Quotes::conversation_D01_quote_W_AAB_rBA ]				= L"Кто ты?";
	data[ Quotes::conversation_D01_quote_W_BAA ]					= L"А что приведёт к ответам?";
	data[ Quotes::conversation_D01_quote_W_BAB_q ]					= L"Ну и чёрт с ними, куда шёл, туда и пойду!";
	data[ Quotes::conversation_D01_quote_PG_BAAA_ev ]				= L"Да ничего не приведёт, сам думай, Ильгиз, я лишь немного поспособствую.";
	data[ Quotes::conversation_D02_quote_PG_00_rt ]					= L"Ну, как продвигается?";
	data[ Quotes::conversation_D02_quote_W_A ]						= L"Не очень, это проклятое поле кажется бескрайним.";
	data[ Quotes::conversation_D02_quote_W_B ]						= L"Отвечай, что ты такое! Зачем в поле заперла?";
	data[ Quotes::conversation_D02_quote_PG_AA_ev ]					= L"И всё вы края ищете, торопитесь, злитесь.\nРаз хочешь, чтоб к краю подтолкнули, так тому и быть!";
	data[ Quotes::conversation_D02_quote_PG_BA_ev ]					= L"Самое обычное природное явление, такое же, как и ты,\nда и не запирали тебя, грубиян! А коли выйти хочешь,\nсразу и говори. Что бы обо мне не говорили,\nа мысли я читать, увы, не умею.";

	data[ Quotes::Button_Quote ]									= L"...";

	return data;
}