#include "World.hpp"
#include "Game.hpp"
#include <iostream>

World::World(Game* game)
	: mSceneGraph(new SceneNode(game))
	, mGame(game)
	, mPlayerAircraft(nullptr)
	, mBackground(nullptr)
	, mWorldBounds(-1.5f, 1.5f, 200.0f, 0.0f) //Left, Right, Down, Up
	, mSpawnPosition(0.f, 0.f)
	, mScrollSpeed(1.0f)
{
}

void World::update(const GameTimer& gt)
{
	while (!mCommandQueue.isEmpty()) {
		mSceneGraph->onCommand(mCommandQueue.pop(), gt);
		std::cout << "Test\n";
	}

	mSceneGraph->update(gt);
}

void World::draw(RenderContext context)
{
	mSceneGraph->draw(context);
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::buildScene()
{
	std::unique_ptr<PlayerAircraft> player(new PlayerAircraft(mGame));
	mPlayerAircraft = player.get();
	mPlayerAircraft->setPosition(0, 0.5, 0.0);
	mPlayerAircraft->setScale(0.75, 0.75, 0.75);
	//mPlayerAircraft->setVelocity(1.0f, 0.0f, 0.0f);
	mSceneGraph->attachChild(std::move(player));

	//std::unique_ptr<Aircraft> enemy1(new Aircraft(Aircraft::Raptor, mGame));
	//auto raptor = enemy1.get();
	//raptor->setPosition(0.5, 0.1, -0.5);
	//raptor->setScale(0.5, 0.5, 0.5);
	//raptor->setWorldRotation(0, 0, 0);
	////raptor->setVelocity(0.0f, 0.1f, 0.0f);
	//mPlayerAircraft->attachChild(std::move(enemy1));

	//std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mGame));
	//auto raptor2 = enemy2.get();
	//raptor2->setPosition(-0.5, 0.1, -0.5);
	//raptor2->setScale(0.5, 0.5, 0.5);
	//raptor2->setWorldRotation(0, 0, 0);
	////raptor2->setVelocity(0.0f, 0.1f, 0.0f);
	//mPlayerAircraft->attachChild(std::move(enemy2));

	//std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame));
	//auto mBackground = backgroundSprite.get();
	//mBackground->setPosition(0, 0, 0.0);
	//mBackground->setScale(10.0, 1.0, 200.0);
	//mBackground->setVelocity(XMFLOAT3(0.0f, 0.0f, -mScrollSpeed));
	//mSceneGraph->attachChild(std::move(backgroundSprite));

	mSceneGraph->build();
}
