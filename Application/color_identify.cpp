#include "color_identify.hpp"

sf::Color getColor( Colors::ID id )
{
	switch ( id )
    {
    case Colors::GUI_active:		return { 0xff, 0xff, 0xff, 255 };
    case Colors::GUI_inactive:		return { 0xaa, 0xaa, 0xaa, 255 };
    case Colors::GUI_locked:		return { 0x88, 0x88, 0x88, 255 };

    case Colors::Menu_background:	return { 0x10, 0x10, 0x10, 255 };

    case Colors::Font_muted:		return { 0xbb, 0xbb, 0xbb, 255 };
	}
}
