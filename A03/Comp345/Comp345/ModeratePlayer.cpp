#include "ModeratePlayer.h"

void ModeratePlayer::SelectCard() {
	cout << "AUTOMATICALLY SECTING MODERATE CARD" << endl;
}

int ModeratePlayer::PlaceNewArmies() {
	cout << "ACTING LIKE A MODERATE PLAYER" << endl;
	int dest;
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
		cin >> dest;
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
int ModeratePlayer::MoveArmies(int numOfMoves) {
	cout << "ACTING LIKE A MODERATE PLAYER" << endl;
	int movementCost = 0;
	int src, dest;
	bool exit = false;
	if (!GetPlayer()->HasArmiesOnBoard()) {
		cout << "SORRY, cannot perform action (No armies to move)" << endl;
		GetPlayer()->PrintPlacedArmies();
		return COST_ONE_ACTIONVALUE;
	}
	while (true) {
		cout << "Here are VALID inputs: " << endl;
		GetPlayer()->PrintPlacedArmies();
		cout << GetPlayer()->GetLastName() << " - MOVE FROM (-1 to skip): ";
		cin >> src;
		if (GetPlayer()->HasSkipped(src)) return COST_ONE_ACTIONVALUE;
		if (!GetPlayer()->HasArmyAtLocation(src)) {
			cout << endl << "WARNING - You do not have any armies at territory ID: " << src << endl;
			continue;
		}
		Territory* source = GetPlayer()->GetTerritory(src);

		//Get all possible moves from src territory and print them
		vector<int> possibleMoves = MasterGame->map->GetMovementCost(src, GetPlayer()->GetBonusFlying());
		cout << "Legal moves from territory " << src << " with " << numOfMoves << " movement points: " << endl;
		for (int i = 0; i < possibleMoves.size(); i++) {
			if (possibleMoves[i] <= numOfMoves && i != src) {
				cout << "Territory " << i << " (move cost: " << possibleMoves[i] << ")" << endl;
			}
		}

		cout << GetPlayer()->GetLastName() << " - MOVE TO (-1 to skip): ";
		cin >> dest;
		if (GetPlayer()->HasSkipped(dest)) return COST_ONE_ACTIONVALUE;
		if (GetPlayer()->GetTerritory(dest) == nullptr) continue;
		Territory* destination = GetPlayer()->GetTerritory(dest);
		Cube* srcArmy = GetPlayer()->GetArmyAtLocation(src);
		movementCost = possibleMoves[dest];
		if (movementCost <= numOfMoves && movementCost > 0) {
			cout << "This move will cost " << movementCost << " move(s). Do you wish to continue? (Y/N) ";
			string ans;
			cin >> ans;
			if (ans == "N" || ans == "n")
				continue;
			else if (ans == "Y" || ans == "y") {
				srcArmy->location = destination;
				cout << "Moved army from location " << src << " to destination " << dest << endl;
				source->removeArmy(GetPlayer()->GetPosition());						// Updating Map
				destination->addArmy(GetPlayer()->GetPosition());						// Updating Map
				if (!GetPlayer()->Find(destination))								// Updating Player GetTerritories()
					GetPlayer()->GetTerritories().push_back(destination);
				for (int i = 0; i < GetPlayer()->GetTerritories().size(); i++) {		// Updating Player GetTerritories()
					if (GetPlayer()->GetTerritories()[i] == source && source->army_count[GetPlayer()->GetPosition()] == 0 && source->city_count[GetPlayer()->GetPosition()] == 0)
						GetPlayer()->GetTerritories().erase(GetPlayer()->GetTerritories().begin() + i);
				}
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
int ModeratePlayer::BuildCity() {
	Disk* city;
	int dest;
	if (!GetPlayer()->HasArmiesOnBoard()) {
		cout << "Put some armies first, jeez!" << endl;
		return COST_ONE_ACTIONVALUE;
	}
	if (!GetPlayer()->HasCitiesToPlace()) {
		cout << "Are you trying to become a real estate agent o.O? I think not." << endl;
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
		cout << GetPlayer()->GetLastName() << " - BUILD CITY AT (-1 to skip): " << endl;
		cin >> dest;
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
int ModeratePlayer::DestroyArmy() {
	int enemy, battlefieldTerrId;
	Territory* battlefieldTerr = nullptr;
	if (!GetPlayer()->HasArmiesOnBoard()) {
		cout << "Attacking with no armies... Pathetic..." << endl;
		GetPlayer()->PrintPlacedArmies();
		return COST_ZERO_ACTIONVALUE;
	}
	while (true) {
		cout << "Here are VALID inputs: " << endl;
		GetPlayer()->PrintPlacedArmies();
		cout << GetPlayer()->GetLastName() << " - DESTROY AT (-1 to skip)? ";
		cin >> battlefieldTerrId;
		if (GetPlayer()->HasSkipped(battlefieldTerrId)) return COST_ONE_ACTIONVALUE;
		if (GetPlayer()->GetTerritory(battlefieldTerrId) == nullptr) continue;
		if (!GetPlayer()->HasArmyAtLocation(battlefieldTerrId)) {
			cout << endl << "There is nobody at " << battlefieldTerrId << "to fight for you! Think again." << endl;
			continue;
		}
		battlefieldTerr = GetPlayer()->GetTerritory(battlefieldTerrId);
		for (int i = 0; i < GetPlayer()->GetTerritory(battlefieldTerrId)->army_count.size(); i++)
			cout << MasterGame->players[i]->GetLastName() << " at pos " << MasterGame->players[i]->GetPosition() << " has " << GetPlayer()->GetTerritory(battlefieldTerrId)->army_count[i] << " armies at your location" << endl;
		cout << GetPlayer()->GetLastName() << " - DESTROY WHOM (-1 to skip): " << endl;
		cin >> enemy;
		if (GetPlayer()->HasSkipped(battlefieldTerrId)) return COST_ONE_ACTIONVALUE; // Check if wants to skip action
		if (enemy < 0 || enemy >= MasterGame->players.size()) { // Checking if valid player GetPosition()
			cout << "Might as well attack the chair! Find a real opponent." << endl << endl;
			continue;
		}
		if (enemy == GetPlayer()->GetPosition()) {
			cout << "Feel free to punch yourself in real life but not happening in my game!" << endl << endl;
			continue;
		}
		if (MasterGame->players[enemy]->GetBonusImmune()) {
			cout << "You can't attack " << enemy << " because they have the 'Immune to Attack' bonus. Please choose a different target." << endl;
			continue;
		}
		if (battlefieldTerr->army_count[enemy] <= 0) { // Checking if ennemy has armies
			cout << "Now you are attacking straight wind. " << enemy << " does not have anything at " << battlefieldTerr->territoryID << " to destroy. " << endl << endl;
			continue;
		}
		MasterGame->players[enemy]->RemoveArmy(battlefieldTerr); // Destroying Army
		cout << "BANG BANG. You shot him down, BANG BANG. " << MasterGame->players[enemy]->GetLastName() << " hit the gound. BANG bang ...(at territory id " << battlefieldTerrId << ") That awful sound.." << endl;
		MasterGame->players[enemy]->PrintPlayerStatus();
		return COST_ONE_ACTIONVALUE;
	}
}
int ModeratePlayer::AndOrAction() {
	cout << "ACTING LIKE A MODERATE PLAYER" << endl;
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
			cin >> choice;
			if (choice < 0 || choice > currentCard->actionCount) {
				cout << "Invalid input, please try again. " << endl;
				continue;
			}
			break;
		}
	}
	return choice;
}