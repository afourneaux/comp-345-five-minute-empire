#include "Game.h"
#include <iostream>


// TODO: Currently, Setup is all hardcoded information. Replace this with
//       proper setup including user input and map loading

vector <Player*> Game::players;
Map* Game::map;

// Get number of players, perform bidding, distribute tokens, generate deck
void Game::Setup() {
	deck = new Deck();
	hand = new Hand(deck);
	playerCount = 3;
	for (int i = 0; i < playerCount; i++) {
		players.push_back(new Player());
		players.at(i)->setPosition(i);
		players.at(i)->SetLastName("defaultPlayer" + to_string(i + 1));
	}
	int* arr = new int[4];
	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 1;
	arr[3] = 0;
	map = new Map(arr, 4, playerCount, 2);
	map->AddEdge(0, 1);
	map->AddEdge(0, 2);
	map->AddEdge(0, 3);
	map->AddEdge(1, 3);
	map->AddEdge(1, 2);
	map->AddEdge(2, 3);
	delete[] arr;
	if (playerCount == 2) {
		gameTurns = GAME_TURNS_2_PLAYERS;
	}
	if (playerCount == 3) {
		gameTurns = GAME_TURNS_3_PLAYERS;
	}
	if (playerCount == 4) {
		gameTurns = GAME_TURNS_4_PLAYERS;
	}

	// DEBUG:
	gameTurns = 1;
}

void Game::MainLoop() {
	cout << "Press Enter to start!";
	cin.ignore(INT_MAX, '\n');
	for (int turn = 0; turn < gameTurns; turn++) {
		cout << "XXXXXXXXXXXX" << endl;
		cout << "BEGIN TURN " << turn + 1 << endl;
		cout << "XXXXXXXXXXXX" << endl;
		// Run through each player's turn
		// TODO: Sort by bid
		for (int i = 0; i < GAME_TURNS_3_PLAYERS; i++) {
			for (int currentPlayer = 0; currentPlayer < playerCount; currentPlayer++) {
				PlayerTurn(players.at(currentPlayer));
			}
			cout << "-------------  ROUND " << i + 1 << "  -------------" << endl;
		}
	}
}

// TODO: Make use of the Player::ComputeScore() function to determine the winner
void Game::GetWinner() {
	int player_count = Game::players.size();

	//Compute the final scores for each player
	int* scores = new int[player_count];
	for (int i = 0; i < player_count; i++) {
		scores[i] = Game::players[i]->ComputeScore();
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
			if (Game::players[i]->getCoins() > Game::players[winner_index]->getCoins())
				winner_index = i;
			else if (Game::players[i]->getCoins() == Game::players[winner_index]->getCoins()) {
				//Tiebreaker 2: player with the most armies
				tiebreaker = "have the most armies on the board.";
				if (Game::players[i]->getArmiesLeft() < Game::players[winner_index]->getArmiesLeft())
					winner_index = i;
				else if (Game::players[i]->getArmiesLeft() == Game::players[winner_index]->getArmiesLeft()) {
					//Tiebreaker 3: player with the most territories
					tiebreaker = "control the most territories.";
					if(Game::map->getNumberControlledTerritories(i) > Game::map->getNumberControlledTerritories(winner_index))
						winner_index = i;
					else if (Game::map->getNumberControlledTerritories(i) == Game::map->getNumberControlledTerritories(winner_index)) {
						tie_after_tiebreakers = true;
					}
				}
			}
			//Print the result of the tiebreaker
			if (tie_after_tiebreakers) {
				cout << "Players " << winner_index << " and " << i << " are still tied after tiebreakers." << endl;
			}
			else {
				cout << "Player " << winner_index << " wins the tiebreaker because they " << tiebreaker << endl;
			}
		}
	}
	if (tie_after_tiebreakers) {
		cout << "The final score is a tie!" << endl;
	}
	else {
		cout << "And the winner is... Player " << winner_index << "!" << endl;
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
		cout << handIndex << ". \"" << cardAtIndex->name << "\" (" << hand->GetCostAtIndex(handIndex) << " coins)" << endl;
	}

	int desiredCardIndex;
	//player->setCoins(1);
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
				validCardIndex = true;
			}
		}
	}

	// Pay for the card
	player->PayCoin(hand->GetCostAtIndex(desiredCardIndex));
	Card* card = hand->Exchange(desiredCardIndex);
	cout << *card;
	player->DoAction(card);
	player->PlayerStatus();
	// TODO: Add the card to the player object and perform its actions
	// Player.PerformActionOfCard(card) or some equivalent
	delete card;	// TODO: Delete as part of the player destructor
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