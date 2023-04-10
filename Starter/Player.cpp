#pragma once
#include "Player.hpp"
#include "CommandQueue.hpp"
#include "Aircraft.hpp"

#include <map>
#include <string>
#include <algorithm>
#include <iostream>


struct AircraftMover {
	AircraftMover(float vx, float vy, float vz)
		: velocity(vx, vy, vz)
	{
	}

	void operator() (Aircraft& aircraft, const GameTimer& dt) const {
		aircraft.accelerate(velocity, dt);
	}

	XMFLOAT3 velocity;
};

Player::Player()
{
	mKeyBinding['A'] = MoveLeft;
	mKeyBinding['D'] = MoveRight;
	mKeyBinding['S'] = MoveDown;
	mKeyBinding['W'] = MoveUp;
	mKeyBinding['P'] = GetPosition;	

	initializeActions();

	for (auto& pair : mActionBinding) {
		pair.second.category = Category::PlayerAirCraft;
	}
}

void Player::handleEvent(CommandQueue& commands)
{
	
}

void Player::handleRealTimeInput(CommandQueue& commands)
{
	for (auto& pair : mKeyBinding) {

		if (GetAsyncKeyState(pair.first) & 0x8000) {
			auto found = mKeyBinding.find(pair.first);

			if (found != mKeyBinding.end() && isRealTimeAction(found->second))

				commands.push(mActionBinding[found->second]);
			
		}
	}
}

void Player::assignKey(Action action, char key)
{
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	mKeyBinding[key] = action;
}

char Player::getAssignedKey(Action action) const
{
	for (auto pair : mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return NULL;
}

void Player::initializeActions()
{
	const float playerSpeed = 1.0f;

	mActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f, 0.0f));
	mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f, 0.0f));
	mActionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, 0.0f, +playerSpeed));
	mActionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f,0.0f, -playerSpeed));
	mActionBinding[GetPosition].action = [](SceneNode& s, const GameTimer&) {
		std::cout << s.getWorldPosition().x << "," << s.getWorldPosition().y << "," << s.getWorldPosition().z << "\n";
	};
}

bool Player::isRealTimeAction(Action action)
{
	switch (action)
	{
	case MoveLeft:
	case MoveRight:
	case MoveDown:
	case MoveUp:
		return true;

	default:
		return false;
	}
}
