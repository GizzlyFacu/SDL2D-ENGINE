#ifndef GAME_H //usaremos esto en vez de pragma once para mayor compatibilidad
#define GAME_H
#include <SDL3/SDL.h>
#include<glm/glm.hpp>

const int FPS = 1;
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
	Uint64 millisecsPreviusTime = 0;

	void setWindowMode();
	inline bool TicksPassed(Uint64 tickInicial, Uint64 tickActual);

};

#endif

