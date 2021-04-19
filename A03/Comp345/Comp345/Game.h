#pragma once
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include <vector>

using namespace std;

// Constants
const int GAME_TURNS_2_PLAYERS = 1;
const int GAME_TURNS_3_PLAYERS = 10;
const int GAME_TURNS_4_PLAYERS = 8;
const int GAME_TURNS_TOURNAMENT = 20;
const int STARTING_TERRITORY_ARMIES = 4;
const int NEUTRAL_ARMY_COUNT = 10;
const int DEVELOPER_COUNT = 4;
const string DEVELOPERS[DEVELOPER_COUNT] = { "Alexander Fourneaux", "Georges Grondin", "Michael Laplaine-Pereira", "Souheil Al-awar" };

// Declare custom classes to be used
class Player;
class Deck;
class Hand;
class Map;

class Game : public Subject{
public:
	void MainMenu();					// Present the game, select single game or tournament
	void DisplayMenuSplash();			// Display the main title and options menu of the game
	void DisplayCredits();				// Display developers and Concordia information
	void Setup();						// Get number of players, perform bidding, distribute tokens, generate deck
	void Startup();						// Perform initial board setup
	void MainLoop();					// Process each player's turn until the game is over
	void GetWinner();					// Calculate the victorious player and congratulate them
	void PlayerTurn(Player* player);	// Perform the current player's turn
	~Game();							// Destructor
	vector<Player*> players;
	Map* map;
	int bank;
	int GetPlayerCount();
	Hand* GetHand();
	int playerCount;
	int maxPlayerNameLength = 0;
	int currentPlayer = -1;
	bool gameOver = false;
	int winnerIndex = -1;
	int currentTurn;
	bool IsTournament() { return isTournament; }
private:
	Deck* deck;
	Hand* hand;
	int gameTurns;
	GameStateView* gameStateView;
	PlayerStateView* playerStateView;
	bool isTournament;
};

extern Game* MasterGame;
int StartupDriver();
void TestScoreCalculation();
void EnterToContinue();