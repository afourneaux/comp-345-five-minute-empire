// Used to check for memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "Game.h"

extern Game* MasterGame;

int main() {
	MasterGame = new Game();
	MasterGame->Setup();
	MasterGame->MainLoop();
	MasterGame->GetWinner();
	delete MasterGame;

	//Check for memory leaks at the end of execution
	_CrtDumpMemoryLeaks();
}
