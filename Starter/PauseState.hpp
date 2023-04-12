#pragma region step 2
#pragma once

#include "State.hpp"

class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context context);

	virtual void		draw(RenderContext context);
	virtual bool		update(const GameTimer& dt);
	virtual void		OnKeyDown(int key)override;
	virtual void		setUpState();
	virtual void		buildState();

private:
};

#pragma endregion