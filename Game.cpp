#include "Game.h"
#include <iostream>

Game::Game() {
	std::cout << "created new object" << "\n";
	isRunning = false;
	isFullscreen = true;//setWindowMode hay que cambiar despues a RealFullcreen(lecture 21)
}

Game::~Game() {
	std::cout << "deleted object" << "\n";

}

void Game::Initialize() {
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS)) {
		std::cerr << "SDL: Can't initialize SDL" << "\n";
	    return;
	}

	setWindowMode();
	window = SDL_CreateWindow("Default Title", WINDOW_WIDTH, WINDOW_HEIGHT, isFullscreen ? SDL_WINDOW_FULLSCREEN:SDL_WINDOW_BORDERLESS);
	if (!window) {
		std::cerr << "SDL window: Error Creating the main Window" << "\n";
		return;
	}

	renderer = SDL_CreateRenderer(window,NULL);
	if (!renderer) {
		std::cerr << "SDL: Error creating the renderer" << "\n";
		return;
	}
	isRunning = true;
}
void Game::setWindowMode() {
	if (isFullscreen){
		const SDL_DisplayMode* displayMode = SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());
		if (!displayMode)
		{
			std::cerr << "error SDL displayMode: "<< SDL_GetError() << "\n";
			return;
		}
		WINDOW_HEIGHT = displayMode->h;
		WINDOW_WIDTH = displayMode->w;
	}
}

void Game::Destroy() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
void Game::ProcessInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			isRunning = false;
			break;
		case SDL_EVENT_KEY_DOWN:
			if (event.key.key ==SDLK_ESCAPE){
				isRunning = false;
			}
		default:
			break;
		}
	}
}
void Game::Update() {
	//object to update
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Game::Run() {
	while (isRunning){
		ProcessInput();
		Update();
		Render();
	}
}