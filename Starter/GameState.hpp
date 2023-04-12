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
	virtual void		OnKeyDown(int key)override;
	virtual void		setUpState();
	virtual void		buildState();


private:
	Game*				mGame;
	World				mWorld;
	Player&				mPlayer;

	XMFLOAT4							mWorldBounds;
	XMFLOAT2		    				mSpawnPosition;
	float								mScrollSpeed;

	PlayerAircraft* mPlayerAircraft;
	SpriteNode* mBackground;
	Aircraft* mEnemy;

	bool paused = false;
};

#endif // BOOK_GAMESTATE_HPP