#pragma once
#include "Player.h"
#include "Cards.h"
#include "Map.h"

// Constants
const int CARDS_TO_WIN_2_PLAYERS = 11;
const int CARDS_TO_WIN_3_PLAYERS = 10;
const int CARDS_TO_WIN_4_PLAYERS = 8;

// Declare custom classes to be used
class Player;
class Deck;
class Map;
class Hand;

class Game {
public:
	void Setup();			// Get number of players, perform bidding, distribute tokens, generate deck
	void MainLoop();		// Process each player's turn until the game is over
	void GetWinner();		// Calculate the victorious player and congratulate them
private:
	Player* players;
	Deck* deck;
	Map* map;
	Hand* hand;
	int playerCount;
};