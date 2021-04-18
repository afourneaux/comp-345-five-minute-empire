#include<iostream>
#include <algorithm>
#include "HumanPlayer.h"
using namespace std;

void HumanPlayer::SelectCard() {
	cout << "You have " << GetPlayer()->GetCoins() << " coins." << endl;
	cout << "Please select a card to draw:" << endl;
	for (int handIndex = 0; handIndex < HAND_SIZE; handIndex++) {
		Card* cardAtIndex = MasterGame->GetHand()->GetCardAtIndex(handIndex);
		if (cardAtIndex == nullptr) {
			continue;
		}
		cout << handIndex << ". \"" << cardAtIndex->name << "\" (" << MasterGame->GetHand()->GetCostAtIndex(handIndex) << " coins)" << endl;
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
			if (GetPlayer()->GetCoins() < MasterGame->GetHand()->GetCostAtIndex(desiredCardIndex)) {
				cout << "You cannot afford this card. You have " << GetPlayer()->GetCoins() << " coins." << endl;
			}
			else {
				if (MasterGame->GetHand()->GetCardAtIndex(desiredCardIndex) == nullptr) {
					cout << "No card exists in space " << desiredCardIndex << endl;
				}
				else {
					validCardIndex = true;
				}
			}
		}
	}

	// Pay for the card
	GetPlayer()->PayCoin(MasterGame->GetHand()->GetCostAtIndex(desiredCardIndex));
	Card* card = MasterGame->GetHand()->Exchange(desiredCardIndex);
	cout << *card;
	GetPlayer()->DoAction(card);
	GetPlayer()->PrintPlayerStatus();
}
int HumanPlayer::PlaceNewArmies() {
	int dest;
	bool found = false;
	// Loop
	cin >> dest;
	return dest;
}
vector<int> HumanPlayer::MoveArmies(int numOfMoves) {
	int randomized;
	int src = -1, dest = -1, count = 0, movementCost;
	bool exit = false, found = false;
	vector<int> choices;
	cin >> src;
	cout << src << endl;
	if (GetPlayer()->HasSkipped(src)) return choices;		// Checks if player skipped
	if (!GetPlayer()->HasArmyAtLocation(src)) {							//  Checks if player has army at source location
		cout << endl << "WARNING - You do not have any armies at territory ID: " << src << endl;
		count++;
		return choices;
	}
	Territory* source = GetPlayer()->GetTerritory(src);
	vector <int> possMoves;
	vector<int> possibleMoves = MasterGame->map->GetMovementCost(src, GetPlayer()->GetBonusFlying());		//Get all possible moves from src territory and print them
	cout << "Legal moves from territory " << src << " with " << numOfMoves << " movement points: " << endl;
	for (int i = 0; i < possibleMoves.size(); i++) {
		if (possibleMoves[i] <= numOfMoves && i != src) {				// Store possible moves that are eligble with num of moves available
			cout << "Territory " << i << " (move cost: " << possibleMoves[i] << ")" << endl;
			possMoves.push_back(i);
		}
	}

	cout << GetPlayer()->GetLastName() << " - MOVE TO (-1 to skip): ";
	cin >> dest;
	cout << dest << endl;
	choices.push_back(src);
	choices.push_back(dest);
	return choices;
}
int HumanPlayer::BuildCity() {
	bool found = false;
	int randomized, dest;
	cin >> dest;
	cout << dest << endl;
	return dest;
}
vector<int> HumanPlayer::DestroyArmy() {
	int enemy = 0, battlefieldTerrId = -1, count = 0;
	Territory* battlefieldTerr = nullptr;
	vector<int> choices;
	bool found = false;
	bool validInput = false;
	while (validInput == false) {
		cin >> battlefieldTerrId;
		if (cin.fail()) {
			cout << "Please input a number" << endl;
			// Clear the CIN buffer
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			continue;
		}
		if (battlefieldTerrId == -1) {
			break;
		}
		battlefieldTerr = MasterGame->map->GetTerritory(battlefieldTerrId);
		if (battlefieldTerr == nullptr) {
			continue;
		}
		validInput = true;
	}
	if (count >= 5)
		battlefieldTerrId = -1;
	if (GetPlayer()->HasSkipped(battlefieldTerrId)) return choices;							// Check if player skipped
	if (GetPlayer()->GetTerritory(battlefieldTerrId) == nullptr) return choices;			// Check if territory is valid
	if (!GetPlayer()->HasArmyAtLocation(battlefieldTerrId)) {								// Check if player has armies at the battlefield territory
		cout << endl << "There is nobody at " << battlefieldTerrId << " to fight for you! Think again." << endl;
		count++;
		return choices;
	}
	for (int i = 0; i <  battlefieldTerr->army_count.size(); i++)
		cout << MasterGame->players[i]->GetLastName() << " at pos " << MasterGame->players[i]->GetPosition() << " has " << battlefieldTerr->army_count[i] << " armies at your location" << endl;
	cout << GetPlayer()->GetLastName() << " - DESTROY WHOM (-1 to skip): ";

	validInput = false;
	while (validInput == false) {
		cin >> enemy;
		if (cin.fail()) {
			cout << "Please input a number" << endl;
			// Clear the CIN buffer
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			continue;
		}
		if (enemy < -1 || enemy >= MasterGame->players.size()) {
			cout << "The selected player does not exist" << endl;
			continue;
		}
		validInput = true;
	}
	choices.push_back(battlefieldTerrId);
	choices.push_back(enemy);
	return choices;
}
int HumanPlayer::AndOrAction() {
	int choice = -1;
	cin >> choice;
	return choice;
}