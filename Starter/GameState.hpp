#ifndef BOOK_GAMESTATE_HPP
#define BOOK_GAMESTATE_HPP

#include "State.hpp"
#include "World.hpp"
#include "Player.hpp"

#include "../Common/GameTimer.h"

//#include <SFML/Graphics/Sprite.hpp>
//#include <SFML/Graphics/Text.hpp>


class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	virtual void		draw(RenderContext context);
	virtual bool		update(const GameTimer& dt);
	//virtual bool		handleEvent(const sf::Event& event);


private:
	World				mWorld;
	Player&				mPlayer;
};

#endif // BOOK_GAMESTATE_HPP