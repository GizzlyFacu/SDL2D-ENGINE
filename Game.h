#ifndef GAME_H //usaremos esto en vez de pragma once para mayor compatibilidad
#define GAME_H
#include <SDL3/SDL.h>

class Game
{
public:
	Game();
	~Game();
	
	void Initialize();
	void Destroy();

	void ProcessInput();
	void Update();
	void Render();
	void Run();


private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool isRunning;
	bool isFullscreen;
	unsigned int WINDOW_WIDTH = 800;
	unsigned int WINDOW_HEIGHT = 600;

	void setWindowMode();

};

#endif

