#pragma once

#include "CommandQueue.hpp"
#include <map>

class CommandQueue;

class Player {
public: 
											Player();
	void									handleEvent(CommandQueue& commands);
	void									handleRealTimeInput(CommandQueue& commands);

	enum Action {
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		GetPosition,
		ActionCount
	};
	enum ActionState {
		Unpressed, 
		Pressed,
	};
	void									assignKey(Action action, char key);
	char									getAssignedKey(Action action) const;

private:
	void									initializeActions();
	static bool								isRealTimeAction(Action action);

private:
	std::map<char, Action>					mKeyBinding;
	std::map<Action, Command>				mActionBinding;
	std::map<Action, ActionState>			mActionStateMapping;
};