#ifndef BOOK_STATE_HPP
#define BOOK_STATE_HPP

#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"

#include "../Common/GameTimer.h"

#include <memory>

class StateStack;
class Player;
class Game;
struct RenderContext;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(Game& game, Player& player);

		Game* game;
		Player* player;
	};


public:
	State(StateStack& stack, Context context);
	virtual				~State();

	virtual void		draw(RenderContext context) = 0;
	virtual bool		update(const GameTimer& dt) = 0;
	//virtual bool		handleEvent(const sf::Event& event) = 0;


protected:
	void				requestStackPush(States::ID stateID);
	void				requestStackPop();
	void				requestStateClear();

	Context				getContext() const;


private:
	StateStack*			mStack;
	Context				mContext;
};

#endif // BOOK_STATE_HPP
