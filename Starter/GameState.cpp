#include "GameState.hpp"



GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(*context.world)
	, mPlayer(*context.player)
{
}

void GameState::draw()
{
	//mWorld.draw(cmdList, mCurrFrameResource);
}

bool GameState::update(const GameTimer& dt)
{
	mWorld.update(dt);

	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealTimeInput(commands);

	return true;
}