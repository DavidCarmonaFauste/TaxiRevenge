#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "MainState.h"
#include "GasMainMenu.h"
#include "GasFillMenu.h"
#include "ShopState.h"
#include "Level2State.h"
#include "Reticule.h"



GameStateMachine::GameStateMachine() {

	currentState_ = "default";
}

GameStateMachine::~GameStateMachine() {
	for (auto state : STATES_) {
		delete state.second; state.second = nullptr;
	}
	STATES_.clear();
}

void GameStateMachine::setState(const string &s) {
	if (currentState_ != "default") 
		STATES_[currentState_]->end();

	currentState_ = s;

	STATES_[currentState_]->start();
}


string GameStateMachine::get_CurrentStateName() const {
	return currentState_;
}

GameState * GameStateMachine::get_CurrentState()  {
	return STATES_[currentState_];
}

void GameStateMachine::initStates() {
	// Main menu
	STATES_.insert(std::pair<string, GameState*>(NAME_MAINMENU_STATE, new MainMenuState()));
	// Main game
	STATES_.insert(std::pair<string, GameState*>(NAME_MAIN_STATE, new MainState()));
	STATES_[NAME_MAIN_STATE]->loadTilemap ();
	// Gas main menu
	STATES_.insert (std::pair<string, GameState*> (NAME_GAS_MAIN_STATE, new GasMainMenu ()));
	// Gas fill menu
	STATES_.insert (std::pair<string, GameState*> (NAME_GAS_FILL_STATE, new GasFillMenu ()));
	// Shop state
	STATES_.insert(std::pair<string, GameState*>(NAME_SHOP_STATE, new ShopState()));
	// Level 2 state
	STATES_.insert (std::pair<string, GameState*> (NAME_LEVEL_2_STATE, new Level2State ()));
	STATES_[NAME_LEVEL_2_STATE]->loadTilemap ();

	//primer estado al ejectuar app
	//...

	//DEPURACION
	//setState(NAME_MAINMENU_STATE);
	setState(NAME_MAINMENU_STATE);
}

void GameStateMachine::fromMainStateToLevel2 () {
	if (currentState_ == NAME_MAIN_STATE) {
		STATES_[currentState_]->end();

		currentState_ = NAME_LEVEL_2_STATE;

		if (!level2StartedOnce_) {
			STATES_[currentState_]->start ();
			level2StartedOnce_ = true;
		}
		else {
			static_cast<Level2State*> (STATES_[currentState_])->awakeMap ();
		}
		Vehicle::getInstance ()->saveSpawnPoint (Vehicle::getInstance ()->getLevel2SpawnPoint ());
	}
}

void GameStateMachine::fromMainStateToGasMainMenu () {
	if (currentState_ == NAME_MAIN_STATE) {
		STATES_[currentState_]->end();
		currentState_ = NAME_GAS_MAIN_STATE;

		if (!gasMainMenuStartedOnce_) {
			STATES_[currentState_]->start ();
			gasMainMenuStartedOnce_ = true;
		}
	}
}

void GameStateMachine::fromLevel2ToMainState () {
	if (currentState_ == NAME_LEVEL_2_STATE) {
		STATES_[currentState_]->end();
		currentState_ = NAME_MAIN_STATE;
		static_cast<MainState*> (STATES_[currentState_])->awakeMap ();
		Vehicle::getInstance ()->saveSpawnPoint (Vehicle::getInstance ()->getLevel1OpenSpawnPoint ());
	}
}

void GameStateMachine::fromGasMainMenuToMainState () {
	if (currentState_ == NAME_GAS_MAIN_STATE) {
		STATES_[currentState_]->end();
		currentState_ = NAME_MAIN_STATE;
		static_cast<MainState*> (STATES_[currentState_])->awakeMap ();
	}
}

void GameStateMachine::fromGasMainMenuToFillMenu () {
	if (currentState_ == NAME_GAS_MAIN_STATE) {
		currentState_ = NAME_GAS_FILL_STATE;
		
		if (!gasFillMenuStartedOnce_) {
			STATES_[currentState_]->start ();
			gasFillMenuStartedOnce_ = true;
		}
		if (gasFillMenuStartedOnce_)
			STATES_[NAME_GAS_FILL_STATE]->updateState();
	}
}

void GameStateMachine::fromGasMainMenuToShopMenu()
{
	if (currentState_ == NAME_GAS_MAIN_STATE) {
		currentState_ = NAME_SHOP_STATE;

		if (!ShopMenuStartedOnce_) {
			STATES_[currentState_]->start();
			ShopMenuStartedOnce_ = true;
		}

		if (ShopMenuStartedOnce_)
			STATES_[NAME_SHOP_STATE]->updateState();
	}
}

void GameStateMachine::fromFillMenuToGasMainMenu () {
	if (currentState_ == NAME_GAS_FILL_STATE || currentState_ == NAME_SHOP_STATE) {
		currentState_ = NAME_GAS_MAIN_STATE;
	}
}
