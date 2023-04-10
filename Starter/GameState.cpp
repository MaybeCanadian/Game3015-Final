#include "GameState.hpp"
#include "Game.hpp"



GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(context.game)
	, mPlayer(*context.player)
{

}

void GameState::draw(RenderContext context)
{
	mWorld.draw(context);
}

bool GameState::update(const GameTimer& dt)
{
	mWorld.update(dt);

	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealTimeInput(commands);

	return true;
}