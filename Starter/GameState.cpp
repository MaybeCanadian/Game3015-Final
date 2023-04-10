#include "GameState.hpp"


GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(*context.world)
	, mPlayer(*context.player)
{

}

void GameState::draw(Game::RenderContext context)
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
