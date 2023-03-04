#pragma once
#include "SceneNode.hpp"
#include "Aircraft.hpp"
#include "PlayerAircraft.hpp"
#include "SpriteNode.h"
#include "CommandQueue.hpp"
#include "Command.hpp"

class World 
{
public:
	explicit							World(Game* window);
	void								update(const GameTimer& gt);
	void								draw(ID3D12GraphicsCommandList* cmdList, FrameResource* mCurrFrameResource);
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
