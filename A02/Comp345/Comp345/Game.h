#pragma once
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include <vector>

using namespace std;

// Constants
const int GAME_TURNS_2_PLAYERS = 13;
const int GAME_TURNS_3_PLAYERS = 10;
const int GAME_TURNS_4_PLAYERS = 8;

// Declare custom classes to be used
struct Player;
class Deck;
class Hand;
class Map;

class Game {
public:
	void Setup();						// Get number of players, perform bidding, distribute tokens, generate deck
	void MainLoop();					// Process each player's turn until the game is over
	void GetWinner();					// Calculate the victorious player and congratulate them
	void PlayerTurn(Player* player);	// Perform the current player's turn
	~Game();							// Destructor
	vector<Player*> players;
	Map* map;
	int bank;
	int GetPlayerCount();
	Hand* GetHand();
private:
	Deck* deck;
	Hand* hand;
	int playerCount;
	int gameTurns;
};

extern Game* MasterGame;
int StartupDriver();
void TestScoreCalculation();
