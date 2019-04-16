#pragma once
#include "GameState.h"
#include "Vehicle.h"
#include "Button.h"


static void mockCallback () {
}

static void exitGameCallback () {
	Game::getInstance ()->setGameEnd ();
}

static void mainStateCallback () {
	Game::getInstance()->setState(NAME_MAIN_STATE);
}


class MainMenuState :
	public GameState
{
public:

	MainMenuState();
	virtual ~MainMenuState();

	virtual void start();

	virtual void update (Uint32 deltaTime);
	

private:
	map<string, Button*> buttons_;
	soundId Sound_NewGameButton_;

	Container* mainBackground_;
	Animation* mainTitleAnm_;
};

