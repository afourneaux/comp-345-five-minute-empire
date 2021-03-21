#include "Game.h"
#include <iostream>
#include "MapLoader.h"

Game* MasterGame;

// Get number of players, perform bidding, distribute tokens, generate deck
void Game::Setup() {
	//------------------------------------------//
	//------------- MAP VARIABLES --------------//
	//------------------------------------------//
	char mapVersion = 'a';						// Map version (a, b)
	bool invalid = true;						// true for invalid, false for valid
	string mapInput;							// Stores the name of the map to be ran

	//----------- ------------------------------//
	//------------ PLAYER VARIABLES ------------//
	//------------------------------------------//
	string playerName = "";						// Container for a player's name

	cout << endl;
	cout << "#----------------------------------#" << endl;
	cout << "#            MAIN MENU             #" << endl;
	cout << "#----------------------------------#" << endl;

	//----------- ------------------------------//
	//-------- DECIDE NUMBER OF PLAYERS --------//
	//------------------------------------------//
	do {
		cout << "\n(Number of players must be between 2 and 4)" << endl;
		cout << "Input number of players and press [ENTER]: ";
		cin >> playerCount;
		if (playerCount >= 2) {
			if (playerCount <= 4) {
				invalid = false;
			}
		}
	} while (invalid);

	cout << endl;

	//------------------------------------------//
	//------------ CREATE PLAYERS --------------//
	//------------------------------------------//
	Player* player;
	// Getting player names
	for (int i = 0; i < playerCount; i++) {
		player = new Player();
		cout << "Enter the name of Player " << i + 1 << ": ";
		cin >> playerName;
		player->SetLastName(playerName);
		player->setPosition(i);
		players.push_back(player);
	}
	cout << endl << "Players for this game are: " << endl;
	for (int j = 0; j < playerCount; j++) {
		cout << j + 1 << ". " << players[j]->GetLastName() << endl;
	}

	//------------------------------------------//
	//---------- DECIDE MAP VERSION ------------//
	//------------------------------------------//
	invalid = true;								// Reset value

	do {
		cout << "\n(Map version must be either 'a' or 'b')" << endl;
		cout << "Input map version and press [ENTER]: ";
		cin >> mapVersion;
		if (mapVersion == 'a' || mapVersion == 'b') {
			invalid = false;
		}
	} while (invalid);

	cout << endl;

	mapInput = "Map" + to_string(playerCount) + mapVersion + ".txt";

	//------------------------------------------//
	//-------------- CREATE MAP ----------------//
	//------------------------------------------//
	MapLoader* mapObject = new MapLoader(mapInput);
	mapObject->readFile();
	map = mapObject->buildMap(mapObject->regions, mapObject->regionsSize, mapObject->players, mapObject->continents);

	cout << "\nX X X X X X X X X X X X X X X X X X X" << endl;
	cout << "       INFORMATION ABOUT DECK" << endl;
	cout << "X X X X X X X X X X X X X X X X X X X\n" << endl;

	//------------------------------------------//
	//---------- CREATE DECK & HAND ------------//
	//------------------------------------------//
	deck = new Deck(playerCount);
	hand = new Hand(deck);

	cout << "Deck size: " << deck->getSize() << endl; // Display number of cards created

	cout << "\nX X X X X X X X X X X X X X X X X X X" << endl;
	cout << "      INFORMATION ABOUT PLAYERS" << endl;
	cout << "X X X X X X X X X X X X X X X X X X X\n" << endl;

	for (int i = 0; i < playerCount; i++) {
		cout << *players[i];
	}
	if (playerCount == 2) {
		gameTurns = GAME_TURNS_2_PLAYERS;
	}
	if (playerCount == 3) {
		gameTurns = GAME_TURNS_3_PLAYERS;
	}
	if (playerCount == 4) {
		gameTurns = GAME_TURNS_4_PLAYERS;
	}
}

void Game::MainLoop() {
	cout << "Press Enter to start!";
	cin.ignore(INT_MAX, '\n');
	cin.ignore(INT_MAX, '\n');

	int startingPlayer = BiddingFacility::DoBidding(players, playerCount);

	for (int turn = 0; turn < gameTurns; turn++) {
		cout << "XXXXXXXXXXXX" << endl;
		cout << "BEGIN ROUND " << turn + 1 << endl;
		cout << "XXXXXXXXXXXX" << endl;
		// Run through each player's turn
		// TODO: Sort by bid
		for (int currentPlayer = startingPlayer; currentPlayer < playerCount + startingPlayer; currentPlayer++) {
			PlayerTurn(players.at(currentPlayer % playerCount));
		}
	}
}

// TODO: Make use of the Player::ComputeScore() function to determine the winner
void Game::GetWinner() {
	int player_count = GetPlayerCount();

	//Compute the final scores for each player
	int* scores = new int[player_count];
	for (int i = 0; i < player_count; i++) {
		scores[i] = players[i]->ComputeScore();
	}

	int winner_index = -1;
	int max_score = -1;
	string tiebreaker = "";
	bool tie_after_tiebreakers = false;
	cout << "Calculating winner and processing tiebreakers: " << endl;
	for (int i = 0; i < player_count; i++) {
		if (scores[i] > max_score) {
			winner_index = i;
			max_score = scores[i];
			tie_after_tiebreakers = false;
		}
		//In the event that two players are tied, proceed to tiebreakers:
		else if (scores[i] == max_score) {
			cout << "Players " << winner_index << " and " << i << " are tied. Proceeding to tiebreakers..." << endl;
			//Tiebreaker 1: player with the most coins
			tiebreaker = "have the most coins.";
			if (players[i]->getCoins() > players[winner_index]->getCoins())
				winner_index = i;
			else if (players[i]->getCoins() == players[winner_index]->getCoins()) {
				//Tiebreaker 2: player with the most armies
				tiebreaker = "have the most armies on the board.";
				if (players[i]->getArmiesLeft() < players[winner_index]->getArmiesLeft())
					winner_index = i;
				else if (players[i]->getArmiesLeft() == players[winner_index]->getArmiesLeft()) {
					//Tiebreaker 3: player with the most territories
					tiebreaker = "control the most territories.";
					if(map->getNumberControlledTerritories(i) > map->getNumberControlledTerritories(winner_index))
						winner_index = i;
					else if (map->getNumberControlledTerritories(i) == map->getNumberControlledTerritories(winner_index)) {
						tie_after_tiebreakers = true;
					}
				}
			}
			//Print the result of the tiebreaker
			if (tie_after_tiebreakers) {
				cout << "Players " << players[winner_index]->GetLastName() << " and " << players[i]->GetLastName() << " are still tied after tiebreakers." << endl;
			}
			else {
				cout << "Player " << players[winner_index]->GetLastName() << " wins the tiebreaker because they " << tiebreaker << endl;
			}
		}
	}
	if (tie_after_tiebreakers) {
		cout << "The final score is a tie!" << endl;
	}
	else {
		cout << "And the winner is... Player " << players[winner_index]->GetLastName() << "!" << endl;
	}

}

void Game::PlayerTurn(Player* player) {
	cout << "========================================" << endl;
	cout << player->GetLastName() << " - It is your turn!" << endl;
	cout << "========================================" << endl;

	cout << "Press Enter to continue...";
	// TODO: This requires two taps of enter on the first go.
	//       Figure out a more elegant solution
	cin.ignore(INT_MAX, '\n');
	cin.ignore(INT_MAX, '\n');

	cout << *hand;

	cout << "You have " << player->getCoins() << " coins." << endl;
	cout << "Please select a card to draw:" << endl;
	for (int handIndex = 0; handIndex < HAND_SIZE; handIndex++) {
		Card* cardAtIndex = hand->GetCardAtIndex(handIndex);
		if (cardAtIndex == nullptr) {
			continue;
		}
		cout << handIndex << ". \"" << cardAtIndex->name << "\" (" << hand->GetCostAtIndex(handIndex) << " coins)" << endl;
	}

	int desiredCardIndex;
	bool validCardIndex = false;

	// Select a card from the hand
	while (validCardIndex == false)
	{
		cin >> desiredCardIndex;
		if (cin.fail() || desiredCardIndex < 0 || desiredCardIndex >= HAND_SIZE) {
			cout << "Please enter a number from 0 to " << HAND_SIZE - 1 << endl;
			// Clear the CIN buffer
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else {
			// Card index is valid, check if the player can afford this card
			if (player->getCoins() < hand->GetCostAtIndex(desiredCardIndex)) {
				cout << "You cannot afford this card. You have " << player->getCoins() << " coins." << endl;
			}
			else {
				if (hand->GetCardAtIndex(desiredCardIndex) == nullptr) {
					cout << "No card exists in space " << desiredCardIndex << endl;
				}
				else {
					validCardIndex = true;
				}
			}
		}
	}

	// Pay for the card
	player->PayCoin(hand->GetCostAtIndex(desiredCardIndex));
	Card* card = hand->Exchange(desiredCardIndex);
	cout << *card;
	player->DoAction(card);
	player->PrintPlayerStatus();
	// TODO: Add the card to the player object and perform its actions
	// Player.PerformActionOfCard(card) or some equivalent
	delete card;	// TODO: Delete as part of the player destructor
}

int Game::GetPlayerCount() {
	return players.size();
}

// Destructor
Game::~Game() {
	delete deck;
	delete hand;
	for (int i = 0; i < playerCount; i++) {
		delete players[i];
	}
	delete Game::map;
}