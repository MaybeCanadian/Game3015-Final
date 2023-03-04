#include "PlayerAircraft.hpp"

#pragma once

PlayerAircraft::PlayerAircraft(Game* game) : Aircraft(Type::Eagle, game)
{
	mType = Type::Eagle;
}

void PlayerAircraft::updateCurrent(const GameTimer& gt)
{
	Aircraft::updateCurrent(gt);

	if (getWorldPosition().x < -2) {
		setPosition(-2, getWorldPosition().y, getWorldPosition().z);
	}
	else if (getWorldPosition().x > 2) {
		setPosition(2, getWorldPosition().y, getWorldPosition().z);
	}

	if (getWorldPosition().z < -2) {
		setPosition(getWorldPosition().x, getWorldPosition().y, -2);
	}
	else if (getWorldPosition().z > 2) {
		setPosition(getWorldPosition().x, getWorldPosition().y, 2);
	}
}
