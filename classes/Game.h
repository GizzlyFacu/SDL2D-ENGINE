#ifndef GAME_H //usaremos esto en vez de pragma once para mayor compatibilidad
#define GAME_H
#include <SDL3/SDL.h>
#include<glm/glm.hpp>
#include "Logger.h"
const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game
{
public:
	Game();
	~Game();
	
	void Initialize();
	void Destroy();

	void Setup();
	void ProcessInput();
	void Update(double deltaTime);
	void Render();
	void Run();



private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool isRunning;
	bool isFullscreen;
	unsigned int WINDOW_WIDTH = 800;
	unsigned int WINDOW_HEIGHT = 600;
	int64_t millisecsPreviusTime = 0;
	int64_t millisecsStartTime = 0;
	int64_t millisecsFrameTime = 0;


	void setWindowMode();
};

#endif

