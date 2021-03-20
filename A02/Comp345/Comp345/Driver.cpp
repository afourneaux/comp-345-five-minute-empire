// Used to check for memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "Game.h"

int main() {
	//testPlayer();
	Game* game = new Game();
	game->Setup();
	game->MainLoop();
	game->GetWinner();
	delete game;

	//Check for memory leaks at the end of execution
	_CrtDumpMemoryLeaks();
}
