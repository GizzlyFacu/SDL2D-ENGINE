#include "Game.h"
#include <iostream>
#include <SDL3_image/SDL_image.h>
#include <random>


Game::Game() {
	Logger::Err("Object Created");
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
glm::vec2 objectPosition{};
glm::vec2 objectVelocity{};

void Game::Setup() {
	
	//setup
	objectPosition={ 50.0f,50.0f };
	objectVelocity={ 50.0f,0.0f };//velocidad en x, y
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


void putTexture(){
}
void Game::Update(double deltaTime) {
	int min = -20;
	int max = 20;
	int numero = min + (std::rand() % (max - min + 1));
	int numero2 = min + (std::rand() % (max - min + 1));

	objectPosition.x += objectVelocity.x*deltaTime;
	objectPosition.x += numero * deltaTime;
	objectPosition.y += numero2 * deltaTime;


}
bool flipflop = true;

void Game::Render() {
	//no entiendo porque el "SetRenderDrawColor" colorea el rect
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	

	SDL_FRect tank_layer{ objectPosition.x,objectPosition.y,200,200 };//esto es como un "layer" rectangular
	std::string tank1 = "tank.png";
	std::string tank2 = "tank2.png";
	std::string dir = "./assets/images/";
	dir.append(flipflop ? tank1:tank2);

	SDL_Surface* temp_surface= IMG_Load(dir.c_str());
	SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(renderer,temp_surface);
	SDL_RenderTexture(renderer,temp_texture,NULL,&tank_layer);
	SDL_DestroySurface(temp_surface);
	SDL_DestroyTexture(temp_texture);

	


	SDL_RenderPresent(renderer);//swap to front buffer
	if (flipflop) {
		flipflop = false;
	}
	else
	{
		flipflop = true;
	}
}

void Game::Run() {
	Setup();
	millisecsPreviusTime = SDL_GetTicks();//99
	while (isRunning){
		millisecsStartTime = SDL_GetTicks();//115
		double deltaTime = (millisecsStartTime - millisecsPreviusTime) / 1000.0f;//0.016

		millisecsPreviusTime = millisecsStartTime;

		ProcessInput();
		Update(deltaTime);
		Render();

		millisecsFrameTime = SDL_GetTicks() - millisecsStartTime;
		if (millisecsFrameTime < MILLISECS_PER_FRAME)SDL_Delay(MILLISECS_PER_FRAME-millisecsFrameTime);
		
	}


}
