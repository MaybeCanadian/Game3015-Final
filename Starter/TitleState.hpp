#ifndef BOOK_TITLESTATE_HPP
#define BOOK_TITLESTATE_HPP

#include "State.hpp"


class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);

	virtual void		draw(RenderContext context);
	virtual bool		update(const GameTimer& dt);
	virtual void		OnKeyDown(int key)override;
	virtual void		buildState();
	virtual void		setUpState();


private:
	bool menuPressed = false;
};

#endif // BOOK_TITLESTATE_HPP
