// Used to check for memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "Game.h"
#include "SetupDriver.cpp"

extern Game* MasterGame;

int main() {
	MasterGame = new Game();
	SetupDriver();
	MasterGame->Setup();
	MasterGame->Startup();
	MasterGame->MainLoop();
	MasterGame->GetWinner();
	delete MasterGame;

	//Check for memory leaks at the end of execution
	_CrtDumpMemoryLeaks();
}
