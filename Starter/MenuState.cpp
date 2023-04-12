#include "MenuState.hpp"
#include "Game.hpp"

MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(context.game)
	, mGame(context.game)
{	
}

void MenuState::draw(RenderContext context)
{
	mWorld.draw(context);
}

bool MenuState::update(const GameTimer& dt)
{
	mWorld.update(dt);

	CommandQueue& commands = mWorld.getCommandQueue();
	//mPlayer.handleRealTimeInput(commands);
	return true;
}

void MenuState::OnKeyDown(int key)
{
	if (key == VK_DOWN) {
		currentSelection++;
		if (currentSelection > 1) {
			currentSelection = 0;
		}
		PlayButton->switchState();
		QuitButton->switchState();
		return;
	}

	if (key == VK_UP) {
		currentSelection--;
		if (currentSelection < 0) {
			currentSelection = 1;
		}
		PlayButton->switchState();
		QuitButton->switchState();
		return;
	}

	if (key == VK_RETURN) {
		if (currentSelection == 0) {
			Camera* mCamera = mGame->GetCamera();
			mCamera->Pitch(-175 * Rads);

			requestStackPop();
			requestStackPush(States::Game);
			return;
		}

		if (currentSelection == 1) {
			PostQuitMessage(0);
		}
	}
}

void MenuState::setUpState()
{
	std::unique_ptr<MenuBackground> backgroundSprite(new MenuBackground(mGame));
	auto mBackground = backgroundSprite.get();
	mBackground->setPosition(0, 0, 0);
	mBackground->setScale(1.5, 1.0, 1.05);
	mWorld.addToWorld(std::move(backgroundSprite));

	std::unique_ptr<MenuButton> Play(new MenuButton(mGame, MenuButton::Play, MenuButton::Selected));
	PlayButton = Play.get();
	PlayButton->setPosition(0, 0.1, 0.1);
	PlayButton->setScale(0.2, 1.0, 0.1);
	mWorld.addToWorld(std::move(Play));

	std::unique_ptr<MenuButton> Quit(new MenuButton(mGame, MenuButton::Quit, MenuButton::UnSelected));
	QuitButton = Quit.get();
	QuitButton->setPosition(0.0, 0.1, -0.1);
	QuitButton->setScale(0.2, 1.0, 0.1);
	mWorld.addToWorld(std::move(Quit));

	Camera* camera = mGame->GetCamera();
	camera->SetPosition(0, 1.2, -0.05);
	camera->Pitch(175 * Rads);
}

void MenuState::buildState()
{
	mWorld.buildScene();
}
