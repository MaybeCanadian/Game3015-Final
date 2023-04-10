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

void World::buildRoot()
{
	std::unique_ptr<SpriteNode> root(new SpriteNode(mGame));
	auto mBackground = root.get();
	mBackground->setPosition(0.0, 0.0, 0.0);
	mBackground->setScale(1.0f, 1.0f, 1.0f);
	mBackground->setVelocity(XMFLOAT3(0.0f, 0.0f, 0.0f));
	addToWorld(std::move(root));

	buildScene();
}

void World::buildScene()
{
	mSceneGraph->build();
}

void World::addToWorld(SceneNode::Ptr node)
{
	mSceneGraph->attachChild(std::move(node));
}
