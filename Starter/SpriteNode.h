#pragma once
#include "Entity.hpp"

class SpriteNode :
    public Entity
{
public:
	SpriteNode(Game* game);

private:
	virtual void		updateCurrent(const GameTimer& gt);
	virtual void		drawCurrent(RenderContext context) const;
	virtual void		buildCurrent();
};
