#include "Entity.hpp"

Entity::Entity(Game* game) : SceneNode(game), mVelocity(0, 0, 0)
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

void Entity::accelerate(XMFLOAT3 velocity, const GameTimer& gt)
{
	mVelocity.x += velocity.x * gt.DeltaTime();
	mVelocity.y += velocity.y * gt.DeltaTime();
	mVelocity.z += velocity.z * gt.DeltaTime();
}

void Entity::accelerate(float vx, float vy, float vz, const GameTimer& gt)
{
	mVelocity.x += vx * gt.DeltaTime();
	mVelocity.y += vy * gt.DeltaTime();
	mVelocity.z += vz * gt.DeltaTime();
}

void Entity::updateCurrent(const GameTimer& gt) 
{
	XMFLOAT3 mV;
	mV.x = mVelocity.x * gt.DeltaTime();
	mV.y = mVelocity.y * gt.DeltaTime();
	mV.z = mVelocity.z * gt.DeltaTime();

	move(mV.x, mV.y, mV.z);

	renderer->World = getWorldTransform();
	renderer->NumFramesDirty++;
}
