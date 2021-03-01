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
	map = new Map(new int[4]{ 0, 1, 1, 0 }, 4, playerCount, 2);
	map->AddEdge(0, 1);
	map->AddEdge(0, 2);
	map->AddEdge(0, 3);
	map->AddEdge(1, 3);
	map->AddEdge(1, 2);
	map->AddEdge(2, 3);
}

void Game::MainLoop() {
	bool isGameOver = false;		// Set to true when a player reaches the requisite amount of cards

	while (isGameOver == false) {
		// Setup at the start of a round

		// Run through each player's turn
		// TODO: Sort by bid
		for (int i = 0; i < playerCount; i++) {
			cout << "========================================" << endl;
			cout << players[i].GetLastName() << " - It is your turn!" << endl;
			cout << "========================================" << endl;


		}
		isGameOver = true;

	}
}

// TODO: Make use of the Player::ComputeScore() function to determine the winner
void Game::GetWinner() {
	cout << "The real winner here is you." << endl;
}