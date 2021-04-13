#include "GreedyPlayer.h"
#include "Strategy.h"
#include <stdlib.h>
using namespace std;

void GreedyPlayer::SelectCard() {
	cout << "||||||||||||||||||||||||||||| GREEDY PLAYER AUTOMATION |||||||||||||||||||||||||||||" << endl;
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
					if (card->actions[actionIdx].action == eAction_DestroyArmies || card->actions[actionIdx].action == eAction_BuildCity)
						desiredValues[cardIdx]++;
				}
				if (card->actionChoice == eChoice_Or) {
					if ((card->actions[actionIdx].action == eAction_DestroyArmies || card->actions[actionIdx].action == eAction_BuildCity) && actionIdx == 0)
						first_OR_Max_Desired++;
					if ((card->actions[actionIdx].action == eAction_DestroyArmies || card->actions[actionIdx].action == eAction_BuildCity) && actionIdx == 1)
						last_OR_Max_Desired++;
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
		for (int i = 0; i < HAND_SIZE-1; i++) {
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
	cout << "||||||||||||||||||||||||||||| GREEDY PLAYER AUTOMATION |||||||||||||||||||||||||||||" << endl;
}


int GreedyPlayer::PlaceNewArmies() {
	cout << "ACTING LIKE A GREEDY PLAYER" << endl;
	int dest;
	bool found = false;
	Cube* cube;
	Territory* destination = nullptr;
	while (true) {
		if (!GetPlayer()->HasArmiesToPlace()) {
			cout << "SORRY, cannot perform action (No armies to place) " << endl;
			GetPlayer()->PrintPlacedArmies();
			return COST_ONE_ACTIONVALUE;
		}
		cout << "Here are VALID inputs: " << endl;
		cout << "-> Territory ID (Starting Region): " << MasterGame->map->starting_territory_index << endl;
		GetPlayer()->PrintPlacedCities();
		cube = GetPlayer()->GetRandomArmy();
		cout << GetPlayer()->GetLastName() << " - PLACE NEW ARMY (-1 to skip): ";
		while (!found) {
			int randomized = rand() % (GetPlayer()->GetTerritories().size());
			if (GetPlayer()->GetTerritories()[randomized]->city_count[GetPlayer()->GetPosition()] > 0 || GetPlayer()->GetTerritories()[randomized]->territoryID == MasterGame->map->starting_territory_index) {
				dest = GetPlayer()->GetTerritories()[randomized]->territoryID;
				found = true;
			}
		}
		cout << dest << endl;
		if (GetPlayer()->HasSkipped(dest)) return COST_ONE_ACTIONVALUE;
		if (GetPlayer()->GetTerritory(dest) == nullptr) continue;
		destination = GetPlayer()->GetTerritory(dest);
		if (dest == MasterGame->map->starting_territory_index || destination->city_count[GetPlayer()->GetPosition()] > 0) {
			destination = GetPlayer()->GetTerritory(dest);
			GetPlayer()->AddArmy(destination, cube);
			return COST_ONE_ACTIONVALUE;
		}
		else {
			cout << endl << "WARNING - You cannot place an army at territory ID. " << dest << ". " << endl;
		}
	}  // While(true)
}

int GreedyPlayer::MoveArmies(int numOfMoves) {
	cout << "ACTING LIKE A GREEDY PLAYER" << endl;
	int movementCost = 0, randomized, count = 0;
	int src = -1, dest = -1;
	bool exit = false, found = false;
	if (!GetPlayer()->HasArmiesOnBoard()) {
		cout << "SORRY, cannot perform action (No armies to move)" << endl;
		GetPlayer()->PrintPlacedArmies();
		return COST_ONE_ACTIONVALUE;
	}
	while (true) {
		cout << "Here are VALID inputs: " << endl;
		GetPlayer()->PrintPlacedArmies();
		cout << GetPlayer()->GetLastName() << " - MOVE FROM (-1 to skip): ";
		while (!found) {
			randomized = rand() % (GetPlayer()->GetTerritories().size());
			if (GetPlayer()->GetTerritories()[randomized]->army_count[GetPlayer()->GetPosition()] > 0)
				found = true;
		}
		src = GetPlayer()->GetTerritories()[randomized]->territoryID;
		if (count == 15)
			src = -1;
		cout << src << endl;
		if (GetPlayer()->HasSkipped(src)) return COST_ONE_ACTIONVALUE;
		if (!GetPlayer()->HasArmyAtLocation(src)) {
			cout << endl << "WARNING - You do not have any armies at territory ID: " << src << endl;
			count++;
			continue;
		}
		Territory* source = GetPlayer()->GetTerritory(src);
		vector <int> possMoves;
		//Get all possible moves from src territory and print them
		vector<int> possibleMoves = MasterGame->map->GetMovementCost(src, GetPlayer()->GetBonusFlying());
		cout << "Legal moves from territory " << src << " with " << numOfMoves << " movement points: " << endl;
		for (int i = 0; i < possibleMoves.size(); i++) {
			if (possibleMoves[i] <= numOfMoves && i != src) {
				cout << "Territory " << i << " (move cost: " << possibleMoves[i] << ")" << endl;
				possMoves.push_back(i);
			}
		}

		cout << GetPlayer()->GetLastName() << " - MOVE TO (-1 to skip): ";
		randomized = rand() % possMoves.size();
		dest = possMoves[randomized];
		cout << dest << endl;
		if (GetPlayer()->HasSkipped(dest)) return COST_ONE_ACTIONVALUE;
		if (GetPlayer()->GetTerritory(dest) == nullptr) continue;
		Territory* destination = GetPlayer()->GetTerritory(dest);
		Cube* srcArmy = GetPlayer()->GetArmyAtLocation(src);
		movementCost = possibleMoves[dest];
		if (movementCost <= numOfMoves && movementCost > 0) {
			cout << "This move will cost " << movementCost << " move(s). Do you wish to continue? (Y/N) ";
			string ans;
			ans = "y";
			cout << ans << endl;
			if (ans == "N" || ans == "n")
				continue;
			else if (ans == "Y" || ans == "y") {
				GetPlayer()->MoveArmy(source, destination, srcArmy);
				cout << "Moved army from location " << src << " to destination " << dest << endl;
				return movementCost;
			}
			else {
				cout << "Invalid choice." << endl;
				continue;
			}
		}
		else {
			cout << endl;
			cout << "WARNING -> MOVEMENT COST: " << movementCost << " -> REMAINING MOVES: " << numOfMoves << ") " << endl;
			cout << endl;
			continue;
		}
	}
}


int GreedyPlayer::BuildCity() {
	Disk* city;
	int dest = -1, randomized;
	bool found = false;
	if (!GetPlayer()->HasArmiesOnBoard()) {
		cout << "Put some armies first, jeez!" << endl;
		return COST_ONE_ACTIONVALUE;
	}
	if (!GetPlayer()->HasCitiesToPlace()) {
		cout << "Are you trying to become a real estate agent o.O? I think not. (No more cities to place)" << endl;
		GetPlayer()->PrintPlacedCities();
		return COST_ONE_ACTIONVALUE;
	}
	cout << endl;
	for (int i = 0; i < GetPlayer()->GetDisks().size(); i++)
		if (!GetPlayer()->GetDisks()[i]->isBuilt) {
			city = GetPlayer()->GetDisks()[i];
			break;
		}
	while (true) {
		cout << "Here are VALID inputs: " << endl;
		GetPlayer()->PrintPlacedArmies();
		cout << GetPlayer()->GetLastName() << " - BUILD CITY AT (-1 to skip): ";
		while (!found) {
			randomized = rand() % (GetPlayer()->GetTerritories().size());
			if (GetPlayer()->GetTerritories()[randomized]->army_count[GetPlayer()->GetPosition()] > 0)
				found = true;
		}
		dest = GetPlayer()->GetTerritories()[randomized]->territoryID;
		cout << dest << endl;
		if (GetPlayer()->HasSkipped(dest)) return COST_ONE_ACTIONVALUE;
		if (GetPlayer()->GetTerritory(dest) == nullptr) continue;
		if (GetPlayer()->HasArmyAtLocation(dest)) {
			GetPlayer()->AddCity(GetPlayer()->GetTerritory(dest));
			return COST_ONE_ACTIONVALUE;
		}
		else
			cout << "Don't you dare try to build a city at " << dest << "! You have no armies there! " << dest << "." << endl;
	}
}
int GreedyPlayer::DestroyArmy() {
	int enemy = 0, battlefieldTerrId = -1, count = 0;
	Territory* battlefieldTerr = nullptr;
	bool found = false;
	if (!GetPlayer()->HasArmiesOnBoard()) {
		cout << "Attacking with no armies... Pathetic..." << endl;
		GetPlayer()->PrintPlacedArmies();
		return COST_ZERO_ACTIONVALUE;
	}
	while (true) {
		cout << "Here are VALID inputs: " << endl;
		GetPlayer()->PrintPlacedArmies();
		cout << GetPlayer()->GetLastName() << " - DESTROY AT (-1 to skip)? ";
		for (int i = 0; i < GetPlayer()->GetTerritories().size(); i++) {
			for (int j = 0; j < MasterGame->GetPlayerCount(); j++) {
				if (j == GetPlayer()->GetPosition())
					continue;
				if (GetPlayer()->GetTerritories()[i]->army_count[GetPlayer()->GetPosition()] > 0)
					if (GetPlayer()->GetTerritories()[i]->army_count[j] > 0) {
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
		if (GetPlayer()->HasSkipped(battlefieldTerrId)) return COST_ONE_ACTIONVALUE;
		if (GetPlayer()->GetTerritory(battlefieldTerrId) == nullptr) continue;
		if (!GetPlayer()->HasArmyAtLocation(battlefieldTerrId)) {
			cout << endl << "There is nobody at " << battlefieldTerrId << " to fight for you! Think again." << endl;
			count++;
			continue;
		}
		for (int i = 0; i < GetPlayer()->GetTerritory(battlefieldTerrId)->army_count.size(); i++)
			cout << MasterGame->players[i]->GetLastName() << " at pos " << MasterGame->players[i]->GetPosition() << " has " << GetPlayer()->GetTerritory(battlefieldTerrId)->army_count[i] << " armies at your location" << endl;
		cout << GetPlayer()->GetLastName() << " - DESTROY WHOM (-1 to skip): ";
		cout << enemy << endl;
		if (GetPlayer()->HasSkipped(battlefieldTerrId)) return COST_ONE_ACTIONVALUE; // Check if wants to skip action
		if (enemy < 0 || enemy >= MasterGame->players.size()) { // Checking if valid player GetPosition()
			cout << "Might as well attack the chair! Find a real opponent." << endl << endl;
			count++;
			continue;
		}
		if (enemy == GetPlayer()->GetPosition()) {
			cout << "Feel free to punch yourself in real life but not happening in my game!" << endl << endl;
			count++;
			continue;
		}
		if (MasterGame->players[enemy]->GetBonusImmune()) {
			cout << "You can't attack " << enemy << " because they have the 'Immune to Attack' bonus. Please choose a different target." << endl;
			count++;
			continue;
		}
		if (battlefieldTerr->army_count[enemy] <= 0) { // Checking if ennemy has armies
			cout << "Now you are attacking straight wind. " << enemy << " does not have anything at " << battlefieldTerr->territoryID << " to destroy. " << endl << endl;
			count++;
			continue;
		}
		MasterGame->players[enemy]->RemoveArmy(battlefieldTerr); // Destroying Army
		cout << "BANG BANG. You shot him down, BANG BANG. " << MasterGame->players[enemy]->GetLastName() << " hit the gound. BANG bang ...(at territory id " << battlefieldTerrId << ") That awful sound.." << endl;
		MasterGame->players[enemy]->PrintPlayerStatus();
		return COST_ONE_ACTIONVALUE;
	}
}
int GreedyPlayer::AndOrAction() {
	cout << "ACTING LIKE A GREEDY PLAYER" << endl;
	Card* currentCard = GetPlayer()->GetHand().back(); //Last drawn card
	int choice = -1;
	string and_or;
	if (currentCard->actionChoice == eChoice_And) // For nice output
		and_or = "AND";
	if (currentCard->actionChoice == eChoice_Or) // For nice output
		and_or = "OR";
	if (currentCard->actionChoice == eChoice_None) // For nice output
		and_or = "";
	cout << GetPlayer()->GetLastName() << " - The card you have chosen allows you to " << currentCard->actions[0] << " " << and_or << " " << currentCard->actions[1] << endl;
	GetPlayer()->PrintPlayerStatus();
	if (currentCard->actionChoice == eChoice_Or) {
		cout << GetPlayer()->GetLastName() << " - Since you have the OR card, please choose: " << endl;
		for (int i = 0; i < currentCard->actionCount; i++)
			cout << "Press " << i << ":" << currentCard->actions[i] << endl;
		while (true) {
			int highestValue_first = -1;
			int highestValue_last = -1;
			if (currentCard->actions[0].action == eAction_DestroyArmies || currentCard->actions[0].action == eAction_BuildCity) {
				highestValue_first = currentCard->actions[0].actionValue;
			}
			if (currentCard->actions[1].action == eAction_BuildCity || currentCard->actions[1].action == eAction_DestroyArmies) {
				highestValue_last = currentCard->actions[1].actionValue;
			}
			choice = highestValue_first > highestValue_last ? highestValue_first : highestValue_last;
			if (highestValue_first == -1 && highestValue_last == -1)
				choice = 0;
			if (choice < 0 || choice > currentCard->actionCount) {
				cout << "Invalid input, please try again. " << endl;
				continue;
			}
			break;
		}
	}
	return choice;
}
