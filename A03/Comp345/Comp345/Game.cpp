#include "Game.h"
#include <iostream>
#include "MapLoader.h"
#include "Setup.h"

Game* MasterGame;

void Game::MainMenu() {
	bool isValidInput;
	bool isReadyToPlay = false;
	int menuOption;
	while (isReadyToPlay == false) {
		DisplayMenuSplash();
		isValidInput = false;
		while (isValidInput == false) {
			cin >> menuOption;
			if (cin.fail() || menuOption < 0 || menuOption > 2) {
				cout << "Input invalid";
				// Clear the CIN buffer
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			else {
				isValidInput = true;
			}
		}
		switch (menuOption) {
		case 0:
			DisplayCredits();
			break;
		case 1:
			isTournament = false;
			isReadyToPlay = true;
			break;
		case 2:
			isTournament = true;
			isReadyToPlay = true;
			break;
		default:
			throw "Game::MainMenu - Invalid menu option input escaped validation";
		}
	}
	system("cls");
}

void Game::DisplayMenuSplash() {
	system("cls");
	cout << endl;
	cout << "        __ _                     _             _           __                _          " << endl;
	cout << "     /\\ \\ (_)_ __   ___    /\\/\\ (_)_ __  _   _| |_ ___    /__\\ __ ___  _ __ (_)_ __ ___ " << endl;
	cout << "    /  \\/ / | '_ \\ / _ \\  /    \\| | '_ \\| | | | __/ _ \\  /_\\| '_ ` _ \\| '_ \\| | '__/ _ \\" << endl;
	cout << "   / /\\  /| | | | |  __/ / /\\/\\ \\ | | | | |_| | ||  __/ //__| | | | | | |_) | | | |  __/" << endl;
	cout << "   \\_\\ \\/ |_|_| |_|\\___| \\/    \\/_|_| |_|\\__,_|\\__\\___| \\__/|_| |_| |_| .__/|_|_|  \\___|" << endl;
	cout << "                                                                      |_|               " << endl;
	cout << "                ____   _____  _____  _____  _____  _____  _____ " << endl;
	cout << "               /  _/  /   __\\/   __\\/   __\\/  _  \\|  _  \\/  ___>" << endl;
	cout << "               |  |---|   __||  |_ ||   __||  |  ||  |  ||___  |" << endl;
	cout << "               \\_____/\\_____/\\_____/\\_____/\\__|__/|_____/<_____/" << endl;
	cout << "                                                                " << endl;
	cout << endl << endl << endl;
	cout << "                     Please select an option" << endl;
	cout << "                     0. Credits" << endl;
	cout << "                     1. Standard Game" << endl;
	cout << "                     2. Tournament" << endl;
	cout << endl << endl;
}

void Game::DisplayCredits() {
	cout << endl << endl;
	cout << "#===============#" << endl;
	cout << "|    CREDITS    |" << endl;
	cout << "#===============#" << endl;
	cout << endl;
	for (int i = 0; i < DEVELOPER_COUNT; i++) {
		cout << DEVELOPERS[i] << endl;
	}
	cout << endl;
	cout << "Created for Concordia University's Gina Cody School of Engineering and Computer Science" << endl;
	cout << "COMP 345 - Advanced Program Design with C++ instructed by Nora Houari" << endl;
	cout << "Winter 2021 semester" << endl;
	cout << endl;
	EnterToContinue();
}

// Get number of players, perform bidding, distribute tokens, generate deck
void Game::Setup() {
	cout << endl;
	cout << "#----------------------------------#" << endl;
	cout << "#              SETUP               #" << endl;
	cout << "#----------------------------------#" << endl;
	SetupObj* setupObj = new SetupObj();
	setupObj->RequestPlayers();
	setupObj->MakePlayers();
	setupObj->DisplayMaps();
	setupObj->MakeMap();
	delete setupObj;

	deck = new Deck(playerCount);
	hand = new Hand(deck);

	cout << "Deck size: " << deck->GetSize() << endl; // Display number of cards created

	cout << "\nX X X X X X X X X X X X X X X X X X X" << endl;
	cout << "      INFORMATION ABOUT PLAYERS" << endl;
	cout << "X X X X X X X X X X X X X X X X X X X\n" << endl;

	for (int i = 0; i < playerCount; i++) {
		cout << *players[i];
	}

	if (isTournament) {
		// For tournament play, insist on a maximum number of player turns
		gameTurns = GAME_TURNS_TOURNAMENT / playerCount;
	}
	else {
		// For standard play, play until each player has played a certain number of turns
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
	if (isTournament == false) {
		EnterToContinue();
	}

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
			if (players[i]->GetCoins() > players[winner_index]->GetCoins())
				winner_index = i;
			else if (players[i]->GetCoins() == players[winner_index]->GetCoins()) {
				//Tiebreaker 2: player with the most armies
				tiebreaker = "have the most armies on the board.";
				if (players[i]->GetArmiesLeft() < players[winner_index]->GetArmiesLeft())
					winner_index = i;
				else if (players[i]->GetArmiesLeft() == players[winner_index]->GetArmiesLeft()) {
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

	if (isTournament == false) {
		EnterToContinue();
	}
	
	cout << *map;
	cout << *hand;

	player->GetStrategy()->SelectCard();
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

void EnterToContinue() {
	cout << "Press Enter to continue...";
	cin.ignore(INT_MAX, '\n');
	cin.ignore(INT_MAX, '\n');
}