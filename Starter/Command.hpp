#pragma once

#include "Category.hpp"

#include "../Common/GameTimer.h"

#include <functional>
#include <cassert>

class SceneNode;

struct Command {

	Command();

	std::function<void(SceneNode&, const GameTimer&)>	action;
	unsigned int										category;
	bool												pressed;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, const GameTimer&)> derivedAction(Function fn) {
	return [=](SceneNode& node, const GameTimer& dt) {
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		fn(static_cast<GameObject&>(node), dt);
	};
}
