﻿#include "Game.h"

//singleton patterns
#include "Reticule.h"
#include "Vehicle.h"
#include "ProyectilePool.h"

#include <iostream>

using namespace std;

unique_ptr<Game> Game::instance_ = nullptr;

Game::Game() {
	// Initialization values
	int winX_, winY_;
	winX_ = winY_ = SDL_WINDOWPOS_CENTERED;

	// SDL initialization
	SDL_Init(SDL_INIT_EVERYTHING);
	
	// SDL_Mixer initialization
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		cout << "Error" << Mix_GetError() << endl;

	// SDL_TTF initialization
	TTF_Init();

	window_ = SDL_CreateWindow("Grand Theft Taxi", winX_, winY_,
		winWidth_, winHeight_, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(renderer_, cameraWidth, cameraHeight);
	//SDL_SetRelativeMouseMode(SDL_TRUE); //This line makes mouse movement in the menu state impossible

	world_ = new b2World(b2Vec2(0, 0));

	// Check for errors
	if (window_ == nullptr || renderer_ == nullptr) {
		cout << "SDL initialization failed\n";
	}
	SDL_ShowCursor(0);
}

Game::~Game() {
	//se debe borrar en orden de: último a primero de creación
	delete gmStMachine_; gmStMachine_ = nullptr;
	for (auto it = cameras_.begin(); it != cameras_.end(); it++) {
		delete (*it).second; (*it).second = nullptr;
	}

}

//los eventos los gestiona la aplicaci�n. Conecta directamente con handleEvents del estado actual. 
void Game::handleEvents(Uint32 deltaTime) {
	SDL_Event event;

	while (SDL_PollEvent(&event) && !exit_) {
		// Call the handleEvents of the cameras and the state
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				exit_ = true;
			}
			
			else if (event.key.keysym.sym == SDLK_f) {
				SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
			}
		}
		for (auto cam : cameras_) cam.second->handleInput(deltaTime, event);
		gmStMachine_->get_CurrentState()->handleEvents(deltaTime, event);
		if (event.type == SDL_QUIT) exit_ = true; //exit_ comunica con main a trav�s del m�todo exitGame
	}
}
void Game::update(Uint32 deltaTime)
{
	accumulator_ += deltaTime;
	while (accumulator_ >= step_*1000) {
		world_->Step(step_, velIterations_, posIterations_);
		accumulator_ -= step_*1000;
	}

	// Update the cameras and the state
	gmStMachine_->get_CurrentState()->update(deltaTime);
	for (auto cam : cameras_) cam.second->update(deltaTime);
}
void Game::render(Uint32 deltaTime)
{
	SDL_RenderClear(renderer_);

	// Render the cameras and the state
	for (auto cam : cameras_) cam.second->render(deltaTime);
	gmStMachine_->get_CurrentState()->render(deltaTime);

	SDL_RenderPresent(renderer_);
}

SDL_Renderer * Game::getRenderer()
{
	return renderer_;
}

SDL_Window * Game::getWindow()
{
	return window_;
}

int Game::getWindowWidth()
{
	return winWidth_;
}

int Game::getWindowHeight()
{
	return winHeight_;
}

int Game::getCameraHeight()
{
	return cameraHeight;
}

int Game::getCameraWidth()
{
	return cameraWidth;
}

b2World * Game::getWorld()
{
	return world_;
}

SoundManager * Game::getSoundManager()
{
	return SoundManager::getInstance();
}

Camera * Game::getCamera(cameraType cT)
{
	return cameras_[cT];
}

GameStateMachine * Game::getGameStateMachine()
{
	return gmStMachine_;
}

void Game::setState(string state){
	gmStMachine_->setState(state);
}

void Game::init() {
	cameras_[GAME_CAMERA] = new Camera(1600, 900);
	cameras_[UI_CAMERA] = new Camera(1600, 900);

	//Init Singleton Patterns - //initInstance() only just once. after always use getInstance();
	SoundManager::getInstance()->initInstance();
	Reticule::getInstance()->initInstance();
	Vehicle::getInstance()->initInstance(); //after, in MainState must do initiAtributtes(VehicleInfo r, KeysScheme k);
	ProyectilePool::getInstance()->initInstance();

	// Create the resources singleton for the first time
	// and initialize its states
	gmStMachine_ = new GameStateMachine();
	gmStMachine_->initStates();
}


//Run es llamado desde Main y gestiona los update, render y hangleEvents de los estados
void Game::run() {
	init();

	double lastTime = SDL_GetTicks();
	double deltaTime = lastTime;

	while (!exit_) {
		handleEvents(deltaTime);
		update(deltaTime);
		render(deltaTime);

		// Update the delta time
		deltaTime = SDL_GetTicks() - lastTime;
		lastTime = SDL_GetTicks();
	}

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	Mix_Quit();
	SDL_Quit();
}

//exitGame devuelve el valor del atributo, determina la ruptura del bucle en Main.cpp
bool Game::exitGame() {
	return exit_;
}


