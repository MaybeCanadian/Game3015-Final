#include "TitleState.hpp"
#include "Game.hpp"

TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(context.game)
	, mGame(context.game)
{
}

void TitleState::draw(RenderContext context)
{
	mWorld.draw(context);
}

bool TitleState::update(const GameTimer& dt)
{
	return true;
}

void TitleState::OnKeyDown(int key)
{
	Camera* camera = mGame->GetCamera();
	camera->Pitch(-175 * Rads);

	requestStackPop();
	requestStackPush(States::Menu);
}

void TitleState::buildState()
{
	mWorld.buildScene();
}

void TitleState::setUpState()
{
	std::unique_ptr<MenuBackground> backgroundSprite(new MenuBackground(mGame));
	auto mBackground = backgroundSprite.get();
	mBackground->setPosition(0, 0, 0);
	mBackground->setScale(1.5, 1.0, 1.05);
	mWorld.addToWorld(std::move(backgroundSprite));

	Camera* camera = mGame->GetCamera();
	camera->SetPosition(0, 1.2, -0.05);
	camera->Pitch(175 * Rads);
}