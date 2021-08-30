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

	data[ Quotes::conversation_D01_quote_PG_00 ]					= L"����������, ������, ������� ������ �� ����.\n�����, ��� ���� ���� �� ������ ������� ����?";
	data[ Quotes::conversation_D01_quote_W_A ]						= L"����������, �������, � ������ �� ������ �� ���?";
	data[ Quotes::conversation_D01_quote_W_B ]						= L"� � �����, ���� �� ��� ������, �� ���� �����������...";
	data[ Quotes::conversation_D01_quote_PG_AA ]					= L"� ������ � ���� ����, � ����� �� ����, � �����,\n���� ����� ��������� � ��� ��� ���� ����� ������ ����.\n��� ������ ����� ���� ���������, �� ���� ��� ����������.";
	data[ Quotes::conversation_D01_quote_PG_BA ]					= L"��� ������, � ��� ������ ����� ����,\n����, ����� ������, �� ��� ������, �� ��������?\n��� ������� ���� � ���� ��������, �� ����� �� � �������.";
	data[ Quotes::conversation_D01_quote_W_AAA_rBA ]				= L"� � �� ��� ����� �������, ����� �� ���, �� ��� � ���� ������.";
	data[ Quotes::conversation_D01_quote_W_AAB_rBA ]				= L"��� ��?";
	data[ Quotes::conversation_D01_quote_W_BAA ]					= L"� ��� ������� � �������?";
	data[ Quotes::conversation_D01_quote_W_BAB_q ]					= L"�� � ���� � ����, ���� ���, ���� � �����!";
	data[ Quotes::conversation_D01_quote_PG_BAAA_ev ]				= L"�� ������ �� �������, ��� �����, ������, � ���� ������� �������������.";
	data[ Quotes::conversation_D02_quote_PG_00_rt ]					= L"��, ��� ������������?";
	data[ Quotes::conversation_D02_quote_W_A ]						= L"�� �����, ��� ��������� ���� ������� ����������.";
	data[ Quotes::conversation_D02_quote_W_B ]						= L"�������, ��� �� �����! ����� � ���� �������?";
	data[ Quotes::conversation_D02_quote_PG_AA_ev ]					= L"� �� �� ���� �����, ����������, �������.\n��� ������, ���� � ���� �����������, ��� ���� � ����!";
	data[ Quotes::conversation_D02_quote_PG_BA_ev ]					= L"����� ������� ��������� �������, ����� ��, ��� � ��,\n�� � �� �������� ����, �������! � ���� ����� ������,\n����� � ������. ��� �� ��� ��� �� ��������,\n� ����� � ������, ���, �� ����.";

	data[ Quotes::Button_Quote ]									= L"...";

	return data;
}