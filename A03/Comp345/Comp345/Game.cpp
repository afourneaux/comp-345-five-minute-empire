#include "Game.h"
#include <iostream>
#include "MapLoader.h"
#include "Setup.h"
#include "GameObservers.h"

Game* MasterGame;

// Get number of players, perform bidding, distribute tokens, generate deck
void Game::Setup() {
	cout << endl;
	cout << "#----------------------------------#" << endl;
	cout << "#            MAIN MENU             #" << endl;
	cout << "#----------------------------------#" << endl;
	SetupObj* setupObj = new SetupObj();
	setupObj->RequestPlayers();
	setupObj->MakePlayers();
	setupObj->DisplayMaps();
	setupObj->MakeMap();
	delete setupObj;

	map->Attach(new GameStateView(this));
	deck = new Deck(playerCount);
	hand = new Hand(deck);

	cout << "Deck size: " << deck->GetSize() << endl; // Display number of cards created

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

void Game::Startup() {
	//Set the starting territory
	vector<int> possibleStartingTerritories = map->GetPotentialStartingTerritories();
	int starter = 0;
	cout << "Please select a starting region (legal options for this map: ";
	for (int i = 0; i < possibleStartingTerritories.size(); i++) cout << possibleStartingTerritories[i] << " ";
	cout << "): ";
	do {
		cin >> starter;
		map->SetStartingTerritory(starter);
	} while (map->starting_territory_index < 0);

	// Add starting armies for each 'human' player to starting territory
	cout << "Placed 4 armies on the starting territory for each active player" << endl;
	for (int i = 0; i < playerCount; i++) {
		for (int j = 0; j < STARTING_TERRITORY_ARMIES; j++) {
			players[i]->PlaceNewArmiesDirectly(map->starting_territory_index);
		}
	}
	// Place neutral armies if 2-player game
	if (playerCount == 2) {
		cout << "Because this is a 2-player game, the players must place 10 armies of a third non-player colour on the map" << endl;
		for (int i = 0; i < NEUTRAL_ARMY_COUNT; i++) {
			bool validPlacement;
			do {
				cout << players[i % 2]->GetLastName() << ", please choose a territory in which to place a neutral army: ";
				int terr;
				cin >> terr;
				validPlacement = players[2]->PlaceNewArmiesDirectly(terr);
			} while (!validPlacement);
		}
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
		for (int currentPlayer = startingPlayer; currentPlayer < playerCount + startingPlayer; currentPlayer++) {
			PlayerTurn(players.at(currentPlayer % playerCount));
		}
	}
}

// Determine and output the winner of the game
void Game::GetWinner() {
	cout << endl;
	cout << "#----------------------------------#" << endl;
	cout << "#  GAME OVER - CALCULATING SCORES  #" << endl;
	cout << "#----------------------------------#" << endl;
	//Compute the final scores for each player
	int* scores = new int[playerCount];
	for (int i = 0; i < playerCount; i++) {
		scores[i] = players[i]->ComputeScore();
	}

	int winner_index = -1;
	int max_score = -1;
	string tiebreaker = "";
	bool tie_after_tiebreakers = false;
	cout << "Calculating winner and processing tiebreakers: " << endl;
	for (int i = 0; i < playerCount; i++) {
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
	cout << endl;
	cout << "#----------------------------------#" << endl;
	cout << "#           FINAL RESULT           #" << endl;
	cout << "#----------------------------------#" << endl;
	if (tie_after_tiebreakers) {
		cout << "The final score is a tie!" << endl;
	}
	else {
		cout << "And the winner is... Player " << players[winner_index]->GetLastName() << "!" << endl;
	}

	delete[] scores;
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
	
	cout << *map;
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
}

int Game::GetPlayerCount() {
	return players.size();
}

// Destructor
Game::~Game() {
	delete deck;
	delete hand;
	for (int i = 0; i < players.size(); i++) {
		delete players[i];
	}
	delete map;
}

Hand* Game::GetHand() {
	return hand;
}