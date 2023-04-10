#include "World.hpp"
#include "Game.hpp"
#include <iostream>

World::World(Game* game)
	: mSceneGraph(new SceneNode(game))
	, mGame(game)
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
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame));
	auto mBackground = backgroundSprite.get();
	mBackground->setPosition(0, 0, 0.0);
	mBackground->setScale(10.0, 1.0, 200.0);
	mBackground->setVelocity(XMFLOAT3(0.0f, 0.0f, -5));
	addToWorld(std::move(backgroundSprite));

	mSceneGraph->build();
}

void World::addToWorld(SceneNode::Ptr node)
{
	mSceneGraph->attachChild(std::move(node));
}
