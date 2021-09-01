#pragma once

//Forward declaration
namespace sf
{
	class Texture;
	class Font;
}
//

namespace Textures
{
	enum ID
	{
		None,

		TitleScreen,
		MainMenuScreen,
			SettingsScreen,
				Controls,
				Image,

		WarningState,
		DialogueState,

		LockedButton,
		DefaultButton,
		SelectedButton,
		PressedButton,
		LockedShortButton,
		DefaultShortButton,
		SelectedShortButton,
		PressedShortButton,
		DefaultLongButton,
		SelectedLongButton,
		PressedLongButton,

		Oleg,
		PeasantGirl,
		UndeadOld,

		Sword,

		WarriorF,
		PeasantGirlF,

		Background01,
		Flash01,
		Background02,
		Foreground01,

		LIMIT
	};
}

namespace Fonts
{
	enum ID
	{
		None,

		RetroGaming,

		_LIMIT
	};
}

namespace Sounds
{
	enum ID
	{
		None,

		_LIMIT
	};
}

//Forward declaration
template < typename Resource, typename Identifier >
class ResourceHolder;
//
typedef ResourceHolder< sf::Texture, Textures::ID > TextureHolder;
typedef ResourceHolder< sf::Font, Fonts::ID > FontHolder;