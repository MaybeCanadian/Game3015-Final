#pragma once
#include "Aircraft.hpp"

class PlayerAircraft
	: public Aircraft
{
public:
	PlayerAircraft(Game* game);

private:
	virtual void		updateCurrent(const GameTimer& gt);
};