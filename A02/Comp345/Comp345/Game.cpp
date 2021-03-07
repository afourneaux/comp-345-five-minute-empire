#include "Game.h"
#include <iostream>

// TODO: Currently, Setup is all hardcoded information. Replace this with
//       proper setup including user input and map loading

// Get number of players, perform bidding, distribute tokens, generate deck
void Game::Setup() {
	deck = new Deck();
	hand = new Hand(deck);
	playerCount = 3;
	players = new Player[playerCount];
	for (int i = 0; i < playerCount; i++) {
		players[i].setLastName("defaultPlayer" + to_string(i + 1));
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
	delete arr;

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
		for (int currentPlayer = 0; currentPlayer < playerCount; currentPlayer++) {
			PlayerTurn(&players[currentPlayer]);
		}
	}
}

// TODO: Make use of the Player::ComputeScore() function to determine the winner
void Game::GetWinner() {
	cout << "The real winner here is you." << endl;
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
	cout << "The number of Coins in the Bank of the game : " << Bank << endl << endl;
	cout << *hand;

	cout << "You have " << player->getCoins() << " coins." << endl;
	cout << "Please select a card to draw:" << endl;
	for (int handIndex = 0; handIndex < HAND_SIZE; handIndex++) {
		Card* cardAtIndex = hand->GetCardAtIndex(handIndex);
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
				validCardIndex = true;
			}
		}
	}

	// Pay for the card
	player->PayCoin(hand->GetCostAtIndex(desiredCardIndex));
	Card* card = hand->Exchange(desiredCardIndex);
	Bank -= hand->GetCostAtIndex(desiredCardIndex);
	cout << "\n Bank : " << Bank << endl;

	cout << *card;
	// TODO: Add the card to the player object and perform its actions
	// Player.PerformActionOfCard(card) or some equivalent
	delete card;	// TODO: Delete as part of the player destructor
}

// Destructor
Game::~Game() {
	delete deck;
	delete hand;
	delete[] players;
	delete map;
}