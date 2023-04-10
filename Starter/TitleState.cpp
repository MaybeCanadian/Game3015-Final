#include "TitleState.hpp"
#include "Game.hpp"

TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
	//, mText()
	//, mShowText(true)
	//, mTextEffectTime(sf::Time::Zero)
{
	//mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

	//mText.setFont(context.fonts->get(Fonts::Main));
	//mText.setString("Press any key to start");
	//centerOrigin(mText);
	//mText.setPosition(context.window->getView().getSize() / 2.f);
}

void TitleState::draw(RenderContext context)
{
	//sf::RenderWindow& window = *getContext().window;
	//window.draw(mBackgroundSprite);

	//if (mShowText)
	//	window.draw(mText);
}

bool TitleState::update(const GameTimer& dt)
{
	//mTextEffectTime += dt;

	//if (mTextEffectTime >= sf::seconds(0.5f))
	//{
	//	mShowText = !mShowText;
	//	mTextEffectTime = sf::Time::Zero;
	//}

	return true;
}

void TitleState::buildState()
{
}

//bool TitleState::handleEvent(const sf::Event& event)
//{
//	// If any key is pressed, trigger the next screen
//	if (event.type == sf::Event::KeyPressed)
//	{
//		requestStackPop();
//		requestStackPush(States::Menu);
//	}
//
//	return true;
//}