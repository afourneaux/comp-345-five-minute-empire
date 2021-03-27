#pragma once
#include <iostream>
#include <string>
#include "MapLoader.h"
#include "Player.h"
#include "Cards.h"
#include "Setup.h"
#include "Game.h"

using namespace std;

void SetupDriver() {
	cout << endl;
	cout << "#----------------------------------#" << endl;
	cout << "#            MAIN MENU             #" << endl;
	cout << "#----------------------------------#" << endl;

	SetupObj* setup = new SetupObj();
	setup->RequestPlayers();
	setup->MakePlayers();
	setup->DisplayMaps();
	setup->MakeMap();
}