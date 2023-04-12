#pragma region step 2
#pragma once

#include "State.hpp"

class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context context);

	virtual void		draw(RenderContext context);
	virtual bool		update(const GameTimer& dt);
	virtual void		setUpState();
	virtual void		buildState();
	//virtual bool		handleEvent(const sf::Event& event);


private:
	bool menuPressed = false;
};

#pragma endregion