#pragma once


namespace Category {


	enum Type {

		None = 0,
		Scene = 1 << 0,
		PlayerAirCraft = 1 << 1,
		AlliedAirCraft = 1 << 2,
		EnemyAirCraft = 1 << 3
	};
}
