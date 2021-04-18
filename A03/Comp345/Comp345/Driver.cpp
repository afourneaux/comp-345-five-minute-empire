#include <iostream>
#include "Game.h"

extern Game* MasterGame;

int main() {
	MasterGame = new Game();
	MasterGame->MainMenu();
	MasterGame->Setup();
	MasterGame->Startup();
	MasterGame->MainLoop();
	MasterGame->GetWinner();
	delete MasterGame;
}
