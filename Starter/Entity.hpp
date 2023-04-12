#pragma once
#include "SceneNode.hpp"

class Entity :
    public SceneNode
{
public:
	Entity(Game* game);
	void				setVelocity(XMFLOAT3 velocity);
	void				setVelocity(float vx, float vy, float vz);
	XMFLOAT3			getVelocity() const;
	void				setAcceleration(XMFLOAT3 accel);
	XMFLOAT3			getAcceleration();
	void				accelerate(XMFLOAT3 velocity, const GameTimer&);
	void				accelerate(float vx, float vy, float vz, const GameTimer&);

	virtual	void		updateCurrent(const GameTimer& gt);

public:
	XMFLOAT3		mVelocity;
	XMFLOAT3		mAcceleration;
};

