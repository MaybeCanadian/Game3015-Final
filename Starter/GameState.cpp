#include "GameState.hpp"
#include "Game.hpp"

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mGame(context.game)
	, mWorld(context.game)
	, mPlayer(*context.player)
	, mPlayerAircraft(nullptr)
	, mBackground(nullptr)
	, mWorldBounds(-1.5f, 1.5f, 200.0f, 0.0f) //Left, Right, Down, Up
	, mSpawnPosition(0.f, 0.f)
	, mScrollSpeed(1.0f)
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

void GameState::buildState()
{
	std::unique_ptr<PlayerAircraft> player(new PlayerAircraft(mGame));
	mPlayerAircraft = player.get();
	mPlayerAircraft->setPosition(0, 0.5, 0.0);
	mPlayerAircraft->setScale(0.75, 0.75, 0.75);
	mPlayerAircraft->setVelocity(0.0f, 0.0f, 0.0f);
	mWorld.addToWorld(std::move(player));

	std::unique_ptr<Aircraft> enemy1(new Aircraft(Aircraft::Raptor, mGame));
	auto raptor = enemy1.get();
	raptor->setPosition(0.5, 0.1, -0.5);
	raptor->setScale(0.5, 0.5, 0.5);
	raptor->setWorldRotation(0, 0, 0);
	//raptor->setVelocity(0.0f, 0.1f, 0.0f);
	mWorld.addToWorld(std::move(enemy1));

	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mGame));
	auto raptor2 = enemy2.get();
	raptor2->setPosition(-0.5, 0.1, -0.5);
	raptor2->setScale(0.5, 0.5, 0.5);
	raptor2->setWorldRotation(0, 0, 0);
	//raptor2->setVelocity(0.0f, 0.1f, 0.0f);
	mWorld.addToWorld(std::move(enemy2));

	mWorld.buildScene();
}
