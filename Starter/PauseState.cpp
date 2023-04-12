#pragma region step 3
#include "PauseState.hpp"
#include "Game.hpp"


PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
{

}

void PauseState::draw(RenderContext context)
{
	
}

bool PauseState::update(const GameTimer& dt)
{
	return true;
}

void PauseState::OnKeyDown(int key)
{
	//M key
	if (key == VK_BACK) {
		requestStateClear();
		requestStackPush(States::Menu);
	}
}

void PauseState::setUpState()
{
}

void PauseState::buildState()
{
}

#pragma endregion