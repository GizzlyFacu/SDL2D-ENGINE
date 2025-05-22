#include <iostream>
#include "Game.h"

int main() {
	Game GameEngine;
	GameEngine.Initialize();
	GameEngine.Run();
	GameEngine.Destroy();
	return 0;
}