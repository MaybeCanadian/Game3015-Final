#pragma once
#include "SceneNode.hpp"

class MenuButton :
	public SceneNode
{
public:
	enum Type
	{
		Play,
		Quit
	};
	enum State
	{
		UnSelected,
		Selected
	};

public:
	MenuButton(Game* game, Type type, State start);

	void				switchState();

private:
	virtual void		updateCurrent(const GameTimer& gt);
	virtual void		drawCurrent(RenderContext context) const;
	virtual void		buildCurrent();

private:
	RenderItem* altRenderer;
	std::string			mSprite;
	std::string			mAltSprite;
	State currentState;
};
