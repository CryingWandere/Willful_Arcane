#pragma once

namespace Category
{
	enum Type
	{
		None			= 0,
		Scene			= 1 << 0,
		
		Hero			= 1 << 1,
		Enemy			= 1 << 2,
		NPC				= 1 << 3,

		AlliedWeapon	= 1 << 4,
		EnemyWeapon		= 1 << 5
	};
}