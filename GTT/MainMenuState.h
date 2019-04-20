#pragma once
#include "GameState.h"
#include "Vehicle.h"
#include "Button.h"
#include "Observer.h"



/*static void exitGameCallback () {
	Game::getInstance ()->setGameEnd ();
}*/




class MainMenuState :
	public GameState, public Observer
{
public:

	MainMenuState();
	virtual ~MainMenuState();

	virtual void start();

	virtual void update (Uint32 deltaTime);

	virtual bool receiveEvent(Event& e);
	

private:

	SoundManager* s_;

	map<string, int> Channels_;

	//Background
	Container* mainBackground_ = nullptr;

	//Buttons
	map<string, Button*> buttons_;

	soundId Sound_NewGameButton_;
	//taxi
	Container* Taxi_ = nullptr;
	Animation* Taxi_anm; //necesary for set in this Update
	//title
	Container* Title_ = nullptr;
	Animation* Title_anm; //necesary for set in this Update

	//scene management
	int cont_1;

	bool DEBUG_;

	
};

