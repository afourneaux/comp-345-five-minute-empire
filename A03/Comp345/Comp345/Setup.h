#pragma once
#include "MapLoader.h"
#include "Player.h"
#include "Cards.h"
#include "Game.h"
#include <string>

using namespace std;

struct Player;
class MapLoader;
class Deck;
class Hand;

class SetupObj {
public:
	SetupObj();								// Constructor

	// map variables
	bool invalid;							// true for invalid, false for valid
	string mapInput;						// To store mapName to run & temporarily store map names
	vector<string> mapNames;				// Vector array to store each map name
	int mapChoice;							// To store map choice from user
	
	// player variables
	string playerName;						// Container for a player's name

	// functions
	void RequestPlayers();					// To request and store numbers of players
	void MakePlayers();						// To instantiate players
	void DisplayMaps();						// To print the available maps
	void MakeMap();							// To instantiate maps

private:
	string path;							// To store path to game maps
};