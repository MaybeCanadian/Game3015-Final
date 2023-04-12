#include "TitleState.hpp"
#include "Game.hpp"

TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
{
}

void TitleState::draw(RenderContext context)
{

}

bool TitleState::update(const GameTimer& dt)
{
	return true;
}

void TitleState::OnKeyDown(int key)
{
	requestStackPop();
	requestStackPush(States::Menu);
}

void TitleState::buildState()
{
}

void TitleState::setUpState()
{
}