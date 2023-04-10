#pragma once
#include "Entity.hpp"
#include <string>

class Aircraft :
    public Entity
{
public:
	enum Type
	{
		Eagle,
		Raptor,
	};


public:
	Aircraft(Type type, Game* game);


protected:
	Aircraft();
	virtual void		updateCurrent(const GameTimer& gt);
	virtual void		drawCurrent(RenderContext context) const;
	virtual void		buildCurrent();
	unsigned int		GetCategory() const;


protected:
	Type				mType;
	std::string			mSprite;
};
