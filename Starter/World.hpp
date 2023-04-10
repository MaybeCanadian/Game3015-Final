#pragma once
#include "SceneNode.hpp"
#include "Aircraft.hpp"
#include "PlayerAircraft.hpp"
#include "SpriteNode.h"
#include "CommandQueue.hpp"
#include "Command.hpp"

struct RenderContext;

class World 
{
public:
	explicit							World(Game* game);
	void								update(const GameTimer& gt);
	void								draw(RenderContext context);
	CommandQueue&						getCommandQueue();
	void								buildRoot();
	void								buildScene();
	void								addToWorld(SceneNode::Ptr node);

private:
	CommandQueue						mCommandQueue;


private:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};


private:
	Game*								mGame;

	SceneNode*							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;
};
