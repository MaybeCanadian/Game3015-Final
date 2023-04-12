#pragma region step 3
#include "PauseState.hpp"
#include "Game.hpp"


PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
	, mGame(context.game)
	, mWorld(context.game)
{

}

void PauseState::draw(RenderContext context)
{
	mWorld.draw(context);
}

bool PauseState::update(const GameTimer& dt)
{
	return true;
}

void PauseState::OnKeyDown(int key)
{
	//M key
	if (key == VK_BACK) {
		Camera* mCamera = mGame->GetCamera();
		mCamera->Pitch(-65 * Rads);

		requestStateClear();
		requestStackPush(States::Menu);
	}
}

void PauseState::setUpState()
{
	std::unique_ptr<TextNode> titleText(new TextNode(mGame, TextNode::PauseImage));
	auto text = titleText.get();
	text->setPosition(0, 1.0, 0.2);
	text->setScale(1.0, 1.0, 1.0);
	text->setWorldRotation(-65 * Rads, 0.0f, 0.0f);
	mWorld.addToWorld(std::move(titleText));
}

void PauseState::buildState()
{
	mWorld.buildScene();
}

#pragma endregion