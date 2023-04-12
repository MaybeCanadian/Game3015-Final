#pragma once
#include "SceneNode.hpp"

class TextNode :
	public SceneNode
{
public:
	enum Type {
		TitleText, 
		PauseImage,
		PauseText,
	};
public:
	TextNode(Game* game, Type type);

private:
	virtual void		updateCurrent(const GameTimer& gt);
	virtual void		drawCurrent(RenderContext context) const;
	virtual void		buildCurrent();

private:
	std::string mSprite;
};
