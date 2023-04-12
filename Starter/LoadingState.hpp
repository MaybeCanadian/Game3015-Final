#pragma region step 4

#include "State.hpp"


class LoadingState : public State
{
public:
	LoadingState(StateStack& stack, Context context);

	virtual void			draw(RenderContext context);
	virtual bool			update(const GameTimer& dt);
	virtual void			buildState();
	virtual void			setUpState();	
	//virtual bool			handleEvent(const sf::Event& event);

	void					setCompletion(float percent);

private:
	//sf::Text				mLoadingText;
	//sf::RectangleShape		mProgressBarBackground;
	//sf::RectangleShape		mProgressBar;

	//ParallelTask			mLoadingTask;
};

#pragma endregion
