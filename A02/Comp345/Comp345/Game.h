#pragma once
#include "Player.h"
#include "Cards.h"
#include "Map.h"

// Constants
const int NUM_OF_PLAYERS = 3;
const int GAME_TURNS_2_PLAYERS = 11;
const int GAME_TURNS_3_PLAYERS = 10;
const int GAME_TURNS_4_PLAYERS = 8;

const int STARTING_COINS_2_PLAYERS = 12;
const int STARTING_COINS_3_PLAYERS = 11;
const int STARTING_COINS_4_PLAYERS = 9;
vector <Player*> players;
Map* map;

// Declare custom classes to be used
struct Player;
class Deck;
class Map;
class Hand;

class Game {
public:
	void Setup();						// Get number of players, perform bidding, distribute tokens, generate deck
	void MainLoop();					// Process each player's turn until the game is over
	void GetWinner();					// Calculate the victorious player and congratulate them
	void PlayerTurn(Player* player);	// Perform the current player's turn
	~Game();							// Destructor
private:
	Deck* deck;
	Hand* hand;
	int playerCount;
	int coinBank;
	int gameTurns;
};