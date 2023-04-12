#ifndef BOOK_STATESTACK_HPP
#define BOOK_STATESTACK_HPP

#include "State.hpp"
#include "StateIdentifiers.hpp"

#include "../Common/GameTimer.h"

#include <vector>
#include <utility>
#include <functional>
#include <map>

class StateStack
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};


public:
	explicit			StateStack(State::Context context);

	template <typename T>
	void				registerState(States::ID stateID);

	void				update(const GameTimer& dt);
	void				draw(RenderContext context);
	//void				handleEvent(const sf::Event& event);
	void				build();

	void				pushState(States::ID stateID);
	void				popState();
	void				clearStates();

	void				OnKeyDown(int Key);

	bool				isEmpty() const;


private:
	State::Ptr			createState(States::ID stateID);
	void				applyPendingChanges();


private:
	struct PendingChange
	{
		explicit			PendingChange(Action action, States::ID stateID = States::None);

		Action				action;
		States::ID			stateID;
	};


private:
	std::vector<State::Ptr>								mStack;
	std::vector<PendingChange>							mPendingList;

	State::Context										mContext;
	std::map<States::ID, std::function<State::Ptr()>>	mFactories;
};


template <typename T>
void StateStack::registerState(States::ID stateID)
{
	mFactories[stateID] = [this]()
	{
		return State::Ptr(new T(*this, mContext));
	};
}

#endif // BOOK_STATESTACK_HPP
