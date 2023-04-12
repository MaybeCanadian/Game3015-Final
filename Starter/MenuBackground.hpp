#pragma once
#include "SceneNode.hpp"

class MenuBackground :
	public SceneNode
{
public:
	MenuBackground(Game* game);

private:
	virtual void		updateCurrent(const GameTimer& gt);
	virtual void		drawCurrent(RenderContext context) const;
	virtual void		buildCurrent();
};
