#pragma once
#include "SceneNode.hpp"
#include "Aircraft.hpp"
#include "PlayerAircraft.hpp"
#include "SpriteNode.h"
#include "CommandQueue.hpp"
#include "Command.hpp"
#include "Game.hpp"

class World 
{
public:
	explicit							World(Game* game);
	void								update(const GameTimer& gt);
	void								draw(Game::RenderContext context);
	CommandQueue&						getCommandQueue();
	void								buildScene();

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

	XMFLOAT4							mWorldBounds;
	XMFLOAT2		    				mSpawnPosition;
	float								mScrollSpeed;
	PlayerAircraft*						mPlayerAircraft;
	SpriteNode*							mBackground;
	Aircraft*							mEnemy;
};
