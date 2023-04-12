#include "StateStack.hpp"
#include "Game.hpp"

#include <cassert>

StateStack::StateStack(State::Context context)
	: mStack()
	, mPendingList()
	, mContext(context)
	, mFactories()
{
}

void StateStack::update(const GameTimer& dt)
{
	 //Iterate from top to bottom, stop as soon as update() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->update(dt))
			break;
	}

	/*if (!mStack.empty())
		mStack.back()->update(dt);*/

	applyPendingChanges();
}

void StateStack::draw(RenderContext context)
{
	//mStack.back()->draw(context);
	 //Draw all active states from bottom to top
	for (State::Ptr& state : mStack)
		state->draw(context);
}

void StateStack::build()
{
	//mStack.back()->buildState();
	for (State::Ptr& state : mStack)
		state->buildState();
}

void StateStack::pushState(States::ID stateID)
{
	mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState()
{
	mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates()
{
	mPendingList.push_back(PendingChange(Clear));
}

void StateStack::OnKeyDown(int key)
{
	for (State::Ptr& state : mStack)
		state->OnKeyDown(key);
}

bool StateStack::isEmpty() const
{
	return mStack.empty();
}

State::Ptr StateStack::createState(States::ID stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	return found->second();
}

void StateStack::applyPendingChanges()
{
	bool dirty = false;

	for (PendingChange change : mPendingList)
	{
		dirty = true;

		switch (change.action)
		{
		case Push:
			mStack.push_back(createState(change.stateID));
			mStack.back()->setUpState();
			break;

		case Pop:
			mStack.pop_back();
			break;

		case Clear:
			mStack.clear();
			break;
		}
	}

	if (dirty == true) {
		mContext.game->RebuildItems();
	}

	mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
	: action(action)
	, stateID(stateID)
{
}
