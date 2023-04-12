#pragma region step 3
#include "PauseState.hpp"
#include "Game.hpp"


PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
{

}

void PauseState::draw(RenderContext context)
{
	/*sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mPausedText);
	window.draw(mInstructionText);*/
}

bool PauseState::update(const GameTimer& dt)
{
	return false;
}

void PauseState::setUpState()
{
}

void PauseState::buildState()
{
}

//bool PauseState::handleEvent(const sf::Event& event)
//{
//	if (event.type != sf::Event::KeyPressed)
//		return false;
//
//	if (event.key.code == sf::Keyboard::Escape)
//	{
//		// Escape pressed, remove itself to return to the game
//		requestStackPop();
//	}
//
//	if (event.key.code == sf::Keyboard::BackSpace)
//	{
//		// Escape pressed, remove itself to return to the game
//		requestStateClear();
//		requestStackPush(States::Menu);
//	}
//
//	return false;
//}

#pragma endregion