#ifndef BOOK_MENUSTATE_HPP
#define BOOK_MENUSTATE_HPP

#include "State.hpp"
#include "World.hpp"
#include "Player.hpp"

class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);

	virtual void			draw(RenderContext context);
	virtual bool			update(const GameTimer& dt);
	virtual void			OnKeyDown(int key)override;
	virtual void			setUpState();
	virtual void			buildState();


private:
	enum OptionNames
	{
		Play,
		Exit,
	};


private:
	Game*	mGame;
	World	mWorld;

	MenuButton* PlayButton;
	MenuButton* QuitButton;

	int currentSelection = 0;
};

#endif // BOOK_MENUSTATE_HPP
