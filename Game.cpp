#include "Game.h"
#include <iostream>
#include <SDL3_image/SDL_image.h>



Game::Game() {
	std::cout << "created new object" << "\n";
	isRunning = false;
	isFullscreen = false;//borrar setWindowMode(lecture 21)
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
void Game::Setup() {

	//setup
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
	//fps limitator
	while (!TicksPassed(millisecsPreviusTime + MILLISECS_PER_FRAME, SDL_GetTicks()));// si llega a 16.6=true
	millisecsPreviusTime = SDL_GetTicks();
	//update:
	std::cout << "sas" << "\n";
}

void Game::Render() {
	Setup();
	//no entiendo porque el "SetRenderDrawColor" colorea el rect
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	SDL_FRect tank_layer{ 10,10,200,200 };//esto es como un "layer" rectangular
	SDL_Surface* temp_surface= IMG_Load("./assets/images/tank.png");
	SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(renderer,temp_surface);
	SDL_RenderTexture(renderer,temp_texture,NULL,&tank_layer);
	SDL_DestroySurface(temp_surface);
	SDL_DestroyTexture(temp_texture);

	


	SDL_RenderPresent(renderer);//swap to front buffer
}

void Game::Run() {
	while (isRunning){
		ProcessInput();
		Update();
		Render();
	}
}
inline bool Game::TicksPassed(Uint64 tickInicial, Uint64 tickActual) {
	return (int64_t)(tickActual - tickInicial) >= 0;
}