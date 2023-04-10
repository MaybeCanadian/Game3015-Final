#ifndef BOOK_TITLESTATE_HPP
#define BOOK_TITLESTATE_HPP

#include "State.hpp"


class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);

	virtual void		draw(RenderContext context);
	virtual bool		update(const GameTimer& dt);
	//virtual bool		handleEvent(const sf::Event& event);


private:
	//sf::Sprite			mBackgroundSprite;
	//sf::Text			mText;

	//bool				mShowText;
	//sf::Time			mTextEffectTime;
};

#endif // BOOK_TITLESTATE_HPP
