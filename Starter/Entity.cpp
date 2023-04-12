#include "Entity.hpp"

Entity::Entity(Game* game) : SceneNode(game), mVelocity(0, 0, 0), mAcceleration(0, 0, 0)
{
}

void Entity::setVelocity(XMFLOAT3 velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy, float vz)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
	mVelocity.z = vz;
}

XMFLOAT3 Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::setAcceleration(XMFLOAT3 accel)
{
	mAcceleration = accel;
}

XMFLOAT3 Entity::getAcceleration()
{
	return mAcceleration;
}

void Entity::accelerate(XMFLOAT3 acceleration, const GameTimer& gt)
{
	mAcceleration.x += acceleration.x;
	mAcceleration.y += acceleration.y;
	mAcceleration.z += acceleration.z;
}

void Entity::accelerate(float ax, float ay, float az, const GameTimer& gt)
{
	mAcceleration.x += ax;
	mAcceleration.y += ay;
	mAcceleration.z += az;
}

void Entity::updateCurrent(const GameTimer& gt) 
{
	mVelocity.x += mAcceleration.x * gt.DeltaTime();
	mVelocity.y += mAcceleration.y * gt.DeltaTime();
	mVelocity.z += mAcceleration.z * gt.DeltaTime();

	mAcceleration = XMFLOAT3(0, 0, 0);

	XMFLOAT3 mV;
	mV.x = mVelocity.x * gt.DeltaTime();
	mV.y = mVelocity.y * gt.DeltaTime();
	mV.z = mVelocity.z * gt.DeltaTime();

	move(mV.x, mV.y, mV.z);

	renderer->World = getWorldTransform();
	renderer->NumFramesDirty++;
}
