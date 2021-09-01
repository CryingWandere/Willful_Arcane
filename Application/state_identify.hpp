#pragma once

namespace States
{
	enum ID
	{
		None,

		Title,
		MainMenu,
			Settings,
			Image,
			Audio,
			Controls,
				KeyBindings,
		Credits,

		Dialogue,

		Warning_ETD,

		Alert_WKS,

		LoadingScreen,

		PauseMenu,

		Tutorial,
		Flash,
		Forest,

		Final
	};
}