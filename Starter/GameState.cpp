#include "GameState.hpp"


GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(*context.world)
	, mPlayer(*context.player)
{
}

void GameState::draw()
{
	//mWorld.draw();
}

bool GameState::update(GameTimer& const dt)
{
	mWorld.update(dt);

	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealTimeInput(commands);

	return true;
}

//bool GameState::handleEvent(const sf::Event& event)
//{
//	// Game input handling
//	CommandQueue& commands = mWorld.getCommandQueue();
//	mPlayer.handleEvent(event, commands);
//
//	// Escape pressed, trigger the pause screen
//#pragma region step 1
//	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
//		requestStackPush(States::Pause);
//#pragma endregion
//	return true;
//}