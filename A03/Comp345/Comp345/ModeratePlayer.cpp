#include "ModeratePlayer.h"
#include "Strategy.h"
#include <stdlib.h>
void ModeratePlayer::SelectCard() {
	cout << "||||||||||||||||||||||||||||| MODERATE PLAYER AUTOMATION |||||||||||||||||||||||||||||" << endl;
	cout << "You have " << GetPlayer()->GetCoins() << " coins." << endl;
	cout << "Please select a card to draw:" << endl;
	for (int handIndex = 0; handIndex < HAND_SIZE; handIndex++) {
		Card* cardAtIndex = MasterGame->GetHand()->GetCardAtIndex(handIndex);
		if (cardAtIndex == nullptr) {
			continue;
		}
		cout << handIndex << ". \"" << cardAtIndex->name << "\" (" << MasterGame->GetHand()->GetCostAtIndex(handIndex) << " coins)" << endl;

	}

	int desiredCardIndex = -1;
	bool validCardIndex = false;
	int desiredValues[HAND_SIZE] = { 0 };
	int first_OR_Max_Desired = 0;
	int last_OR_Max_Desired = 0;

	// Select a card from the hand
	while (validCardIndex == false)
	{
		// Checking which card is most desirable based on point system
		for (int cardIdx = 0; cardIdx < HAND_SIZE; cardIdx++) {
			Card* card = MasterGame->GetHand()->GetCardAtIndex(cardIdx);
			if (card == nullptr)
				break;

			for (int actionIdx = 0; actionIdx < card->actionCount; actionIdx++) {
				if (card->actionChoice == eChoice_And || card->actionChoice == eChoice_None) {
					if (card->actions[actionIdx].action == eAction_PlaceArmies || card->actions[actionIdx].action == eAction_MoveArmies)
						desiredValues[cardIdx] = desiredValues[cardIdx] + card->actions[actionIdx].actionValue;
				}
				if (card->actionChoice == eChoice_Or) {
					if ((card->actions[actionIdx].action == eAction_PlaceArmies || card->actions[actionIdx].action == eAction_MoveArmies) && actionIdx == 0)
						first_OR_Max_Desired = card->actions[actionIdx].actionValue;
					if ((card->actions[actionIdx].action == eAction_PlaceArmies || card->actions[actionIdx].action == eAction_MoveArmies) && actionIdx == 1)
						last_OR_Max_Desired = card->actions[actionIdx].actionValue;
				}
			}
			if (card->actionChoice == eChoice_Or)
				desiredValues[cardIdx] = (first_OR_Max_Desired > last_OR_Max_Desired) ? first_OR_Max_Desired : last_OR_Max_Desired;
			//Checking if card is too expensive -> putting it lower cost than 0 so that there is always a choice
			if (MasterGame->GetHand()->GetCostAtIndex(cardIdx) > GetPlayer()->GetCoins())
				desiredValues[cardIdx] = -1;
		}

		// Choosing the card based on the point system
		desiredCardIndex = 0;
		for (int i = 0; i < HAND_SIZE - 1; i++) {
			if (desiredValues[0] < desiredValues[i + 1]) {
				desiredValues[0] = desiredValues[i + 1];
				desiredCardIndex = i + 1;
			}
		}
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
	cout << "||||||||||||||||||||||||||||| MODERATE PLAYER AUTOMATION |||||||||||||||||||||||||||||" << endl;
}

int ModeratePlayer::PlaceNewArmies() {
	int dest, count = 0;
	bool found = false;
	// Loop
	while (!found) {													// Randomly chooses a territory that has armies in it
		cout << "..";
		if (count == 10)
			return -1;
		int randomized = rand() % (GetPlayer()->GetTerritories().size());
		if (GetPlayer()->GetTerritories()[randomized]->city_count[GetPlayer()->GetPosition()] > 0 || GetPlayer()->GetTerritories()[randomized]->territoryID == MasterGame->map->starting_territory_index) {
			dest = GetPlayer()->GetTerritories()[randomized]->territoryID;
			found = true;
		}
	}
	cout << dest << endl;
	return dest;
}

vector<int> ModeratePlayer::MoveArmies(int numOfMoves) {

	int randomized;
	int src = -1, dest = -1, count = 0, movementCost;
	bool exit = false, found = false;
	vector<int> choices;
	while (!found) {													// Randomizes player territories to see which one has armies in it
		randomized = rand() % (GetPlayer()->GetTerritories().size());
		if (GetPlayer()->GetTerritories()[randomized]->army_count[GetPlayer()->GetPosition()] > 0)
			found = true;
	}
	src = GetPlayer()->GetTerritories()[randomized]->territoryID;
	if (count == 15)
		src = -1;
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
	if (possMoves.size() == 0)
		return choices;
	cout << GetPlayer()->GetLastName() << " - MOVE TO (-1 to skip): ";
	randomized = rand() % possMoves.size();								// Randomizes all possible moves
	dest = possMoves[randomized];
	cout << dest << endl;
	choices.push_back(src);
	choices.push_back(dest);
	return choices;
}


int ModeratePlayer::BuildCity() {
	bool found = false;
	int randomized, dest;
	while (!found) {												// Randomizes territories that contain army
		randomized = rand() % (GetPlayer()->GetTerritories().size());
		if (GetPlayer()->GetTerritories()[randomized]->army_count[GetPlayer()->GetPosition()] > 0) {
			found = true;
			dest = GetPlayer()->GetTerritories()[randomized]->territoryID;
		}
	}
	return dest;
}
vector<int> ModeratePlayer::DestroyArmy() {
	int enemy = 0, battlefieldTerrId = -1, count = 0;
	Territory* battlefieldTerr = nullptr;
	vector<int> choices;
	bool found = false;
	for (int i = 0; i < GetPlayer()->GetTerritories().size(); i++) { // Loop through all current player territories
		for (int j = 0; j < MasterGame->GetPlayerCount(); j++) { // Loop through all players
			if (j == GetPlayer()->GetPosition())					// Check if it's self
				continue;
			if (GetPlayer()->GetTerritories()[i]->army_count[GetPlayer()->GetPosition()] > 0)	// Check if player has army at location
				if (GetPlayer()->GetTerritories()[i]->army_count[j] > 0) { // Check if other players have army at location
					found = true;
					battlefieldTerrId = GetPlayer()->GetTerritories()[i]->territoryID;
					enemy = j;
					break;
				}
		}
		if (found)
			break;
	}
	cout << battlefieldTerrId << endl;
	battlefieldTerr = MasterGame->map->GetTerritory(battlefieldTerrId);
	if (count >= 5)
		battlefieldTerrId = -1;
	if (GetPlayer()->HasSkipped(battlefieldTerrId)) return choices;	// Check if player skipped
	if (GetPlayer()->GetTerritory(battlefieldTerrId) == nullptr) return choices;			// Check if territory is valid
	if (!GetPlayer()->HasArmyAtLocation(battlefieldTerrId)) {						// Check if player has armies at the battlefield territory
		cout << endl << "There is nobody at " << battlefieldTerrId << " to fight for you! Think again." << endl;
		count++;
		return choices;
	}
	for (int i = 0; i < GetPlayer()->GetTerritory(battlefieldTerrId)->army_count.size(); i++)
		cout << MasterGame->players[i]->GetLastName() << " at pos " << MasterGame->players[i]->GetPosition() << " has " << GetPlayer()->GetTerritory(battlefieldTerrId)->army_count[i] << " armies at your location" << endl;
	cout << GetPlayer()->GetLastName() << " - DESTROY WHOM (-1 to skip): ";
	cout << enemy << endl;
	choices.push_back(battlefieldTerrId);
	choices.push_back(enemy);
	return choices;
}
int ModeratePlayer::AndOrAction() {
	int choice = -1;
	Card* currentCard = GetPlayer()->GetHand().back();
	if (currentCard->actionChoice == eChoice_Or) {
		cout << GetPlayer()->GetLastName() << " - Since you have the OR card, please choose: " << endl;
		for (int i = 0; i < currentCard->actionCount; i++)
			cout << "Press " << i << ":" << currentCard->actions[i] << endl;
		while (true) {
			int highestValue_first = -1;
			int highestValue_last = -1;
			if (currentCard->actions[0].action == eAction_PlaceArmies || currentCard->actions[0].action == eAction_MoveArmies) {
				highestValue_first = currentCard->actions[0].actionValue;
			}
			if (currentCard->actions[1].action == eAction_PlaceArmies || currentCard->actions[1].action == eAction_MoveArmies) {
				highestValue_last = currentCard->actions[1].actionValue;
			}
			choice = highestValue_first > highestValue_last ? 0 : 1;
			if (highestValue_first == -1 && highestValue_last == -1)
				choice = 0;
			if (choice < -1 || choice > currentCard->actionCount) {
				cout << "Invalid input, please try again. " << endl;
				continue;
			}
			else if (choice == -1){
				choice = 0;
			}
			break;
		}
	}
	return choice;
}