#pragma once

#include < SFML/Graphics/Color.hpp >

namespace Colors
{
	enum ID
	{
		None,

		GUI_inactive,
		GUI_active,
		GUI_locked,

		Menu_background,

		Font_muted
	};
}

sf::Color getColor( Colors::ID id );