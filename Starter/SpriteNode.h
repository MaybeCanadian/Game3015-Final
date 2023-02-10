#pragma once
#include "Entity.hpp"

class SpriteNode :
    public Entity
{
public:
	SpriteNode(Game* game);

private:
	virtual void		updateCurrent(const GameTimer& gt) const;
	virtual void		drawCurrent(ID3D12GraphicsCommandList* cmdList, FrameResource* mCurrFrameResource) const;
	virtual void		buildCurrent();
};
