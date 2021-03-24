#pragma once
#include "MapLoader.h"
#include "Player.h"
#include "Cards.h"
#include "Game.h"
#include <string>

using namespace std;

class Player;
class MapLoader;
class Deck;
class Hand;

class Setup {
public:
	Setup();								// Constructor

	// map variables
	bool invalid;							// true for invalid, false for valid
	string mapInput;						// Stores the name of the map to be ran

	// player variables
	string playerName;						// Container for a player's name

	// functions
	void RequestPlayers();					// To request and store numbers of players
	void MakePlayers();
	void DisplayMaps();
	void MakeMap();

private:
	string path;							// To store path to game maps
};