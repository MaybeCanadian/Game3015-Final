#include "MenuState.hpp"
#include "Game.hpp"

#define Rads 3.14/360

MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(context.game)
	, mGame(context.game)

{	
}

void MenuState::draw(RenderContext context)
{
	mWorld.draw(context);
}

bool MenuState::update(const GameTimer& dt)
{
	mWorld.update(dt);

	CommandQueue& commands = mWorld.getCommandQueue();
	//mPlayer.handleRealTimeInput(commands);

	return true;
}

void MenuState::buildState()
{
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame));
	auto mBackground = backgroundSprite.get();
	mBackground->setPosition(0, 0, 0);
	mBackground->setScale(1.0, 2.0, 1.0);
	mBackground->setWorldRotation(-80 * Rads, 0.0f, 0.0f);
	mBackground->setVelocity(XMFLOAT3(0.0f, 0.0f, 0.0f));
	mWorld.addToWorld(std::move(backgroundSprite));

	mWorld.buildScene();
}
