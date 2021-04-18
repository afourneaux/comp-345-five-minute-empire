#include<iostream>
#include <algorithm>
#include "Game.h"
#include "GreedyPlayer.h"
#include "ModeratePlayer.h"
#include "HumanPlayer.h"

using namespace std;

extern Game* MasterGame;

Player::Player(int pos)
{
	if (MasterGame->IsTournament()) {
		InitializePlayerForTournament(pos);
	}
	else {
		InitializePlayer(pos);
	}
	this->bf = new BiddingFacility();
}
//Destructor
Player::~Player()
{
	for (int i = 0; i < cubes.size(); i++)  // iterate through armies
		delete cubes[i];
	for (int i = 0; i < disks.size(); i++) // iterate trough disks
		delete disks[i];
	for (int i = 0; i < hand.size(); i++) // iterate through hand
		delete hand[i];
	delete bf;
}
//copy constructor
Player::Player(const Player* player) {
	//Copying armies
	for (int i = 0; i < player->GetCubes().size(); i++) {
		cubes[i]->isPlaced = player->GetCubes()[i]->isPlaced;
		cubes[i]->location = player->GetCubes()[i]->location;
	}
	//Copying disks
	for (int i = 0; i < player->GetDisks().size(); i++) {
		disks[i]->isBuilt = player->GetDisks()[i]->isBuilt;
		disks[i]->location = player->GetDisks()[i]->location;
	}
	bf = player->GetBf(); //Need copy constructor of Bf
	lastName = player->GetLastName();
	//Copying territories
	for (int i = 0; i < player->GetTerritories().size(); i++) {
		territories[i]->army_count = player->GetTerritories()[i]->army_count;
		territories[i]->city_count = player->GetTerritories()[i]->city_count;
		territories[i]->continentID = player->GetTerritories()[i]->continentID;
		territories[i]->head = player->GetTerritories()[i]->head;
		territories[i]->territoryID = player->GetTerritories()[i]->territoryID;
	}
	armiesLeft = player->armiesLeft;
	coins = player->coins;
}
// Assignment operator
Player& Player::operator= (const Player& player) {
	//Copying armies
	for (int i = 0; i < player.GetCubes().size(); i++) {
		cubes[i]->isPlaced = player.GetCubes()[i]->isPlaced;
		cubes[i]->location = player.GetCubes()[i]->location;
	}
	//Copying disks
	for (int i = 0; i < player.GetDisks().size(); i++) {
		disks[i]->isBuilt = player.GetDisks()[i]->isBuilt;
		disks[i]->location = player.GetDisks()[i]->location;
	}
	bf = player.GetBf(); //Need copy constructor of Bf
	lastName = player.GetLastName();
	//Copying territories
	for (int i = 0; i < player.GetTerritories().size(); i++) {
		territories[i]->army_count = player.GetTerritories()[i]->army_count;
		territories[i]->city_count = player.GetTerritories()[i]->city_count;
		territories[i]->continentID = player.GetTerritories()[i]->continentID;
		territories[i]->head = player.GetTerritories()[i]->head;
		territories[i]->territoryID = player.GetTerritories()[i]->territoryID;
	}
	armiesLeft = player.armiesLeft;
	coins = player.coins;

	return *this;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const Player& player) {
	out << "--- " << player.GetLastName() << " ---" << endl;
	out << "Coins: " << player.GetCoins() << endl;
	//Army locations
	out << "Armies locations: " << endl;
	for (int i = 0; i < player.GetCubes().size(); i++)
		if (player.GetCubes()[i]->isPlaced)
			cout << "ID: " << player.GetCubes()[i]->location->territoryID << endl;
	out << endl;
	//Cities locations
	out << "Disks locations: " << endl;
	for (int i = 0; i < player.GetDisks().size(); i++)
		if (player.GetDisks()[i]->isBuilt)
			cout << "ID: " << player.GetDisks()[i]->location->territoryID << endl;
	cout << endl;
	return out;
}

//If > 0 after payment return true and do transaction, else return false
void Player::PayCoin(int amt) {
	cout << lastName << " is trying to pay " << amt << " coins..." << endl;
	if (coins - amt >= 0) {
		cout << lastName << " - You DO have enough coins. You currently have " << coins << " coins." << endl;
		coins -= amt;
	}
	else {
		cout << lastName << " - You DO NOT have enough coins. You currently have " << coins << " coins." << endl;
	}
	cout << lastName << " now has " << coins << " coins." << endl;
}
//**********
//PlaceNewArmies
//**********
int Player::PlaceNewArmies() {
	int dest;
	const int BIGGESTDIFF = 100;
	int armyDiff = 0, count = 0, smallestDiff = BIGGESTDIFF;
	bool found = false;
	Cube* cube;
	Territory* destination = nullptr;
	Territory* temp = nullptr;
	vector <Territory*> priorityTerr;
	// Loop
	while (true) {
		if (!HasArmiesToPlace()) {							// Check if player has armies to place
			cout << "SORRY, cannot perform action (No armies to place) " << endl;
			PrintPlacedArmies();
			actions.push_back("  - Player wanted to place an army, but has no armies to place.");
			Notify();
			return COST_ONE_ACTIONVALUE;
		}
	cout << "Here are VALID inputs: " << endl;
	cout << "-> Territory ID (Starting Region): " << MasterGame->map->starting_territory_index << endl;
	PrintPlacedCities();
	cube = GetRandomArmy();
	cout << GetLastName() << " - PLACE NEW ARMY (-1 to skip): ";

	dest =  strat->PlaceNewArmies();						//implementing strat

	if (HasSkipped(dest))
	{
		actions.push_back("  - Player skips, did not place an army");
		Notify();
		return COST_ONE_ACTIONVALUE;
	}
	if (GetTerritory(dest) == nullptr) continue;			// Checks if territory exists
	destination = GetTerritory(dest);
	AddArmy(destination, cube);
	actions.push_back("  - Places army in territory " + to_string(dest));
	Notify();
	if (dest == MasterGame->map->starting_territory_index || destination->city_count[GetPosition()] > 0) {			// Check if territory is a valid game ID: Starting region or Has a city
		destination = GetTerritory(dest);
		AddArmy(destination, cube);
		return COST_ONE_ACTIONVALUE;
	}
	else 
		cout << endl << "WARNING - You cannot place an army at territory ID: " << dest << " (You do not have a city there or it's not the starting region" << endl;
	}  // While(true)
}

bool Player::PlaceNewArmiesDirectly(int territoryIndex) {
	bool hasPlaced = false;
	Territory* destination;

	if (GetTerritory(territoryIndex) == nullptr) {
		cout << "Invalid Territory ID " << territoryIndex << ". Please try again." << endl;
		return false;
	}
	destination = GetTerritory(territoryIndex);
	Cube* cube = GetRandomArmy();
	if (cube == nullptr) {
		cout << "Error: failed to place army at Territory ID " << territoryIndex << ", no available armies found." << endl;
		return false;
	}
	AddArmy(destination, cube); // Updating player territories
	return true;
}


//**********
//MoveArmies
//**********
int Player::MoveArmies(int numOfMoves) {
	int movementCost = 0, randomized, count = 0;
	int src = -1, dest = -1;
	Territory* source = nullptr;
	Territory* destination = nullptr;
	bool exit = false, found = false;
	vector<int> choices;
	if (!HasArmiesOnBoard()) {									// Check if player has armies to place
		cout << "SORRY, cannot perform action (No armies to move)" << endl;
		PrintPlacedArmies();
		actions.push_back("  - Player wanted to move an army, but has no armies to move.");
		Notify();
		return COST_ONE_ACTIONVALUE;
	}
	// Loop
	while (true) {
		cout << "Here are VALID inputs: " << endl;
		PrintPlacedArmies();
		cout << GetLastName() << " - MOVE FROM (-1 to skip): ";
		
		choices = strat->MoveArmies(numOfMoves);				// Implementing Strat

		src = choices[0];
		dest = choices[1];
		if (HasSkipped(src)) {
			actions.push_back("  - Player skips, did not move armies");
			Notify();
			return COST_ONE_ACTIONVALUE;
		}
		if (HasSkipped(dest))
		{
			actions.push_back("  - Player skips, did not move armies.");
			Notify();
			return COST_ONE_ACTIONVALUE;
		}
		if (GetTerritory(dest) == nullptr) continue;			// Check if territory is valid
		movementCost = MasterGame->map->GetMovementCost(src, GetBonusFlying())[dest];
		source = MasterGame->map->GetTerritory(src);
		destination = MasterGame->map->GetTerritory(dest);
		Cube* srcArmy = GetArmyAtLocation(src);
		if (movementCost <= numOfMoves && movementCost > 0) {				// Check if movement cost is within movements left
			cout << "This move will cost " << movementCost << " move(s). Do you wish to continue? (Y/N) ";
			string ans;
			ans = "y";
			cout << ans << endl;
			if (ans == "N" || ans == "n")
				continue;
			else if (ans == "Y" || ans == "y") {
				MoveArmy(source, destination, srcArmy);
				cout << "Moved army from location " << src << " to destination " << dest << endl;
				actions.push_back("  - Moves army from territory " + to_string(src) + " to territory " + to_string(dest));
				Notify();
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
//**********
//MoveOverLand
//**********
bool Player::MoveOverLand() {
	return true;
}
//**********
//MoveOverSea
//**********
bool Player::MoveOverSea() {
	return true;
}
//**********
//BuildCity
//**********
int Player::BuildCity() {
	Disk* city;
	int dest = -1, randomized = -1;
	bool found = false;
	if (!HasArmiesOnBoard()) {								// Check if player has army present on the board (to build the city)
		cout << "Put some armies first, jeez!" << endl;
		return COST_ONE_ACTIONVALUE;
	}
	if (!HasCitiesToPlace()) {								// Check if player has city to build 
		cout << "Are you trying to become a real estate agent o.O? I think not. (No more cities to place)" << endl;
		PrintPlacedCities();
		return COST_ONE_ACTIONVALUE;
	}
	cout << endl;
	for (int i = 0; i < GetDisks().size(); i++)
		if (!GetDisks()[i]->isBuilt) {
			city = GetDisks()[i];
			break;
		}
	while (true) {
		cout << "Here are VALID inputs: " << endl;
		PrintPlacedArmies();
		cout << GetLastName() << " - BUILD CITY AT (-1 to skip): ";

		dest = strat->BuildCity();						//implementing strat

		cout << dest << endl;
		if (HasSkipped(dest)) {
			actions.push_back("  - Player skips, did not build city");
			Notify();
			return COST_ONE_ACTIONVALUE;
		}
		if (GetTerritory(dest) == nullptr) continue;
		if (HasArmyAtLocation(dest)) {
			AddCity(GetTerritory(dest));
			actions.push_back("  - Builds city in territory " + to_string(dest));
			Notify();
			return COST_ONE_ACTIONVALUE;
		}
		else
			cout << "Don't you dare try to build a city at " << dest << "! You have no armies there! " << dest << "." << endl;
	}
}

//**********
//DestroyArmy
//**********
int Player::DestroyArmy() {//Checks if friendly & enemy in same location -> Returns if it was destroyed
	int enemy = 0, battlefieldTerrId = -1, count = 0;
	Territory* battlefieldTerr = nullptr;
	bool found = false;
	vector<int> choices;
	if (!HasArmiesOnBoard()) {
		cout << "Attacking with no armies... Pathetic..." << endl;
		PrintPlacedArmies();
		actions.push_back("  - Player wanted to attack, but has no armies");
		Notify();
		return COST_ZERO_ACTIONVALUE;
	}
	while (true) {														// LOOP
		cout << "Here are VALID inputs: " << endl;
		PrintPlacedArmies();
		cout << GetLastName() << " - DESTROY AT (-1 to skip)? ";
		

		choices = strat->DestroyArmy();							// Impementing Strategy

		battlefieldTerrId = choices[0];
		enemy = choices[1];
		battlefieldTerr = MasterGame->map->GetTerritory(battlefieldTerrId);

		if (count > 5) {
			cout << "Tried too many times";
			break;
		}
		if (HasSkipped(battlefieldTerrId)) {
			actions.push_back("  - Player skips, did not attack anyone");
			Notify();
			return COST_ONE_ACTIONVALUE;
		}
		if (enemy < 0 || enemy >= MasterGame->players.size()) { // Checking if valid player GetPosition()
			cout << "Might as well attack the chair! Find a real opponent." << endl << endl;
			count++;
			continue;
		}
		if (enemy == GetPosition()) {
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
		actions.push_back("  - Destroys army of player " + MasterGame->players[enemy]->lastName + " at territory " + to_string(battlefieldTerrId));
		Notify();
		return COST_ONE_ACTIONVALUE;
	}
}
//**********
//DoAction
//**********
void Player::DoAction(Card* card) {
	bool hasActed = false;
	int possibleActions = 0, cost = 0, receivedCoins = 0;
	hand.push_back(card);						// puts drawn card in the hand of player
	Notify(); // to notify that player has a new card in hand with new values
	//update player with relevant card bonuses
	for (int i = 0; i < card->abilityCount; i++) {
		switch (card->abilities[i].type) {
		case eAbility_PlusOneArmy:
			bonusArmies++;
			break;
		case eAbility_Flying:
			bonusFlying++;
			break;
		case eAbility_PlusOneMove:
			bonusMoves++;
			break;
		case eAbility_Coins:
			receivedCoins = min(MasterGame->bank, card->abilities[i].value);
			cout << "You get " << receivedCoins << " bonus coins from " << card->name << endl;
			coins += receivedCoins;
			break;
		case eAbility_Immune:
			bonusImmune = true;
			break;
		case eAbility_Elixir:
			elixirs += card->abilities[i].value;
			break;
		case eAbility_VpPerCardName:
			for (int j = 0; j < TRACKED_CARD_COUNT; j++) {
				if (card->abilities[i].setName.find(TRACKED_CARD_NAMES[j]) != string::npos) {
					bonusForTrackedName[j] = true;
					break;
				}
			}
			break;
		case eAbility_VpPerCoins:
			bonusForCoins = true;
			break;
		case eAbility_VpPerFlying:
			bonusForFlying = true;
			break;
		}
	}
	// Update count of tracked card names
	for (int i = 0; i < TRACKED_CARD_COUNT; i++) {
		if (card->name.find(TRACKED_CARD_NAMES[i]) != string::npos) {
			cardsByTrackedName[i]++;
			break;
		}
	}

	// Trigger GameStateView update
	Notify();

	int choice = AndOrAction();					// Finds out choice of user
	possibleActions = choice + 1;
	if (card->actionChoice == eChoice_And || card->actionChoice == eChoice_None) {	// AND Card overwrites values
		choice = 0;
		possibleActions = card->actionCount;
	}
	for (; choice < possibleActions; choice++) {
		//apply relevant action bonuses based on cards player owns
		int actionValueWithBonus = card->actions[choice].actionValue;
		if (card->actions[choice].action == eAction_PlaceArmies) {
			actionValueWithBonus += bonusArmies;
			cout << "You currently have a bonus of " << bonusArmies << " when placing armies." << endl;
		}
		else if (card->actions[choice].action == eAction_MoveArmies) {
			actionValueWithBonus += bonusMoves;
			cout << "You currently have a bonus of " << bonusMoves << " moves when moving armies." << endl;
			cout << "You currently have a Flying bonus of " << bonusFlying << " when moving armies over water." << endl;
		}

		for (int i = 0; i < actionValueWithBonus;) {
			cout << endl;
			cout << "Action: " << card->actions[choice].action << endl;
			cout << actionValueWithBonus - i << " moves left" << endl;
			cout << endl;
			switch (card->actions[choice].action) {
			case eAction_BuildCity: cost = BuildCity();
				i += cost;
				cout << endl;
				break;
			case eAction_DestroyArmies: cost = DestroyArmy();
				cout << endl;
				i += cost;
				break;
			case eAction_MoveArmies: cost = MoveArmies(actionValueWithBonus-i);
				i += cost;
				cout << endl;
				break;
			case eAction_PlaceArmies: cost = PlaceNewArmies();
				cout << endl;
				i += cost;
				break;
			default:
				cout << "Found an invalid action for card name:" << card->name;
				cout << endl;
				break;
			}
		}
	}
	PrintPlayerStatus();
}
int Player::ComputeScore() {

	//Calculate the scores for controlled continents + territories
	territoryScore = MasterGame->map->ComputeMapTerritoryScore(position);
	continentScore = MasterGame->map->ComputeMapContinentScore(position);

	cardScore = 0;
	int player_count = MasterGame->players.size();

	//Loop through each card player owns
	for (int card_index = 0; card_index < hand.size(); card_index++) {
		//loop through each ability on each card
		for (int ability_index = 0; ability_index < hand[card_index]->abilityCount; ability_index++) {
			Ability* ability = &hand[card_index]->abilities[ability_index];
			//If the player iteration matches the calling player, compute scores from other points-giving cards
			//If the card grants VP per cardName, count the number of cards with that name
			if (ability->type == eAbility_VpPerCardName) {
				int count = 0;
				for (int i = 0; i < hand.size(); i++) {
					if (hand[i]->name.find(ability->setName) != string::npos) {
						count++;
					}
				}
				if (count >= ability->setTarget) {
					if (ability->countSetOnce)
						cardScore += ability->value;
					else
						cardScore += ability->value * count;
				}
			}
			else if (ability->type == eAbility_VpPerCoins) {
				cardScore += (coins / ability->setTarget) * ability->value;
			}
			else if (ability->type == eAbility_VpPerFlying) {
				int count = 0;
				for (int i = 0; i < hand.size(); i++) {
					for (int j = 0; j < hand[i]->abilityCount; j++) {
						if (hand[i]->abilities[j].type == eAbility_Flying) {
							count++;
						}
					}
				}
				cardScore += ability->value * count;
			}
		}
	}

	int elixir_winner = -1;
	int elixir_max = -1;
	for (int i = 0; i < player_count; i++) {
		if (MasterGame->players[i]->elixirs > elixir_max) {
			elixir_winner = i;
			elixir_max = MasterGame->players[i]->elixirs;
		}
		else if (MasterGame->players[i]->elixirs == elixir_max) {
			elixir_winner = -1;
		}
	}
	if (elixir_winner == position) {
		elixirWinner = true;
		cardScore += ELIXIR_BONUS;
	}
	else {
		elixirWinner = false;
	}

	totalScore = cardScore + territoryScore + continentScore;

	return totalScore;
}

void Player::AddCardToHand(Card* card) {
	hand.push_back(card);
}

//****************************************************************************************************************************************************************************
//                                                                 HELPER METHODS
//****************************************************************************************************************************************************************************

// if OR -> Returns 0 or 1 depending on user inputs which is the action choosen. If AND -> Returns -1 is because we have an AND action
int Player::AndOrAction() {
	int choice = -1;
	Card* currentCard = GetHand().back();
	string and_or;
	if (currentCard->actionChoice == eChoice_And) // For nice output
		and_or = "AND";
	if (currentCard->actionChoice == eChoice_Or) // For nice output
		and_or = "OR";
	if (currentCard->actionChoice == eChoice_None) // For nice output
		and_or = "";
	cout << GetLastName() << " - The card you have chosen allows you to " << currentCard->actions[0] << " " << and_or << " " << currentCard->actions[1] << endl;
	PrintPlayerStatus();
	if (currentCard->actionChoice == eChoice_Or) {
		cout << GetLastName() << " - Since you have the OR card, please choose: " << endl;
		for (int i = 0; i < currentCard->actionCount; i++)
			cout << "Press " << i << ":" << currentCard->actions[i] << endl;
		choice = strat->AndOrAction();
		return choice;
	}
}
//**********
//PrintPrintPlayerStatus
//**********
void Player::PrintPlayerStatus() {
	vector <Territory*> territories = GetTerritories();
	Territory* terr = nullptr;
	cout << endl << "================" << endl;
	cout << lastName << " control statistics:" << endl;
	for (int i = 0; i < territories.size(); i++) {
		terr = territories[i];
		cout << "Territory ID " << terr->territoryID << ": " << terr->army_count[position] << " cube(s) & " << terr->city_count[position] << " disk(s) " << endl;
	}
	cout << "================" << endl;
}
//**********
//GetRandomArmy
//**********
Cube* Player::GetRandomArmy() {
	for (int i = 0; i < cubes.size(); i++)
		if (!cubes[i]->isPlaced)
			return cubes[i];
	return nullptr;
}
//**********
//GetArmyAtLocation
//**********
Cube* Player::GetArmyAtLocation(int id) {
	for (int i = 0; i < cubes.size(); i++)
		if (cubes[i]->location != nullptr && cubes[i]->location->territoryID == id)
			return cubes[i];
	return nullptr;
}
//**********
//GetArmyAtLocation
//**********
Disk* Player::GetCityAtLocation(int id) {
	for (int i = 0; i < disks.size(); i++)
		if (disks[i]->location->territoryID == id) return disks[i];
	return nullptr;
}
Territory* Player::GetTerritory(int id) {
	return MasterGame->map->GetTerritory(id);
}
//**********
//HasArmyAtLocation
//**********

bool Player::HasArmyAtLocation(int id) {
	for (int i = 0; i < cubes.size(); i++)
		if (cubes[i]->location != nullptr && cubes[i]->location->territoryID == id)
			return true;
	return false;
}
//**********
//HasArmyAtLocation
//**********
bool Player::HasCityAtLocation(int id) {
	for (int i = 0; i < disks.size(); i++)
		if (disks[i]->location->territoryID == id) return true;
	return false;
}
//**********
//HasArmiesToPlace
//**********
Cube* Player::HasArmiesToPlace() {
	for (int i = 0; i < cubes.size(); i++) {
		if (!cubes[i]->isPlaced)
			return cubes[i];
	}
	return nullptr;
}
//**********
//HasCitiesToPlace
//**********
Disk* Player::HasCitiesToPlace() {
	for (int i = 0; i < disks.size(); i++) {
		if (!disks[i]->isBuilt)
			return disks[i];
	}
	return nullptr;
}
//**********
//HasCitiesToPlace
//**********
bool Player::HasSkipped(int input) {
	if (input == -1) {
		cout << " * Action skipped * " << endl;
		return true;
	}
	return false;
}
//**********
//Add City
//**********
void Player::AddCity(Territory* terr) {
	terr->addCity(position);			// Updating map territories
	if (!Find(terr))					// Updating Player territories
		territories.push_back(terr);
	for (int i = 0; i < disks.size(); i++) {
		if (!disks[i]->isBuilt) {					// Look for available cubes
			disks[i]->isBuilt = true;
			disks[i]->location = terr;
			cout << lastName << "* Placed * - City unit at territory ID " << terr->territoryID << endl;
			return;
		}
	}
	cout << lastName << " - Player::AddCity() Bug. Should not get here. " << endl;
	return;
}
//**********
//Add Army
//**********
void Player::AddArmy(Territory* terr, Cube* cube) {
	terr->addArmy(position);			// Updating map territories
	if (!Find(terr))					// Updating Player territories
		territories.push_back(terr);
	for (int i = 0; i < territories.size(); i++) {		// Updating Player territories
		if (territories[i] == terr && terr->army_count[position] == 0 && terr->city_count[position] == 0)
			territories.erase(territories.begin() + i);
	}
	cube->isPlaced = true;
	cube->location = terr;
	cout << "* Placed * - Army unit at territory ID " << terr->territoryID << endl;

	return;
}
//**********
//Remove Army
//**********
void Player::RemoveArmy(Territory* terr) {
	terr->removeArmy(position);			// Updating map territories
	for (int i = 0; i < territories.size(); i++) {		// Updating Player territories
		if (territories[i] == terr && terr->army_count[position] == 0 && terr->city_count[position] == 0)
			territories.erase(territories.begin() + i);
	}
	for (int i = 0; i < cubes.size(); i++) {
		if (cubes[i]->location == terr) {					// Look for available cubes
			cubes[i]->isPlaced = false;
			cubes[i]->location = nullptr;
			cout <<"* Removed * - Army unit at territory ID " << terr->territoryID << endl;
			return;
		}
	}
	cout << lastName << " - Player::RemoveArmy() Bug. Should not get here. " << endl;
	return;
}
//**********
//Add Army
//**********
void Player::MoveArmy(Territory* src, Territory* dest, Cube* cube) {
	src->removeArmy(position);
	dest->addArmy(position);			// Updating map territories
	if (!Find(dest))					// Updating Player territories
		territories.push_back(dest);
	for (int i = 0; i < territories.size(); i++) {		// Updating Player territories
		if (territories[i] == src && src->army_count[position] == 0 && src->city_count[position] == 0)
			territories.erase(territories.begin() + i);
	}
	cube->isPlaced = true;
	cube->location = dest;
	cout << "* Placed * - Army unit at territory ID " << dest->territoryID << endl;

	return;
}
//**********
//Find()
//**********
bool Player::Find(Territory* terr) {
	bool found = false;
	for (int i = 0; i < territories.size(); i++)
		if (territories[i] == terr)
			found = true;
	return found;
}
//**********
//PrintPlacedCities
//**********
void Player::PrintPlacedCities() {
	for (int i = 0; i < territories.size(); i++) {
		if (territories[i]->city_count[position] > 0)
			cout << "-> Territory ID (" << territories[i]->city_count[position] << " City(ies)): " << territories[i]->territoryID << endl;
	}
	cout << endl;
}
//**********
//PrintPlacedArmies
//**********
void Player::PrintPlacedArmies() {
	for (int i = 0; i < territories.size(); i++) {
		if (territories[i]->army_count[position] > 0)
			cout << "-> Territory ID (" << territories[i]->army_count[position] << " Army(ies)): " << territories[i]->territoryID << endl;
	}
	cout << endl;
}
//**********
//HasArmiesOnBoard
//**********
bool Player::HasArmiesOnBoard() {
	for (int i = 0; i < cubes.size(); i++)
		if (cubes[i]->isPlaced)
			return true;
	return false;
}
//**********
//InitializePlayer
//**********
void Player::InitializePlayer(int pos) {
	for (int i = 0; i < 18; i++) {
		cubes.push_back(new Cube());
		cubes[i]->isPlaced = false;
	}
	for (int j = 0; j < 3; j++)
		disks.push_back(new Disk());
	string type;
	if (MasterGame->playerCount == 2 && pos == 2)
		return;
	cout << "Enter the name of Player " << pos + 1 << ": ";
	cin >> lastName;
	while (type != "H" && type != "h" && type != "G" && type != "g" && type != "M" && type != "m") {
		cout << endl << lastName << " is what kind of player are you?" << endl;
		cout << "Here are the available chocies: Human (H), Greedy (G), Moderate (M): ";
		cin >> type;

		if (type != "H" && type != "h" && type != "G" && type != "g" && type != "M" && type != "m")
			cout << "Invalid input, please try again." << endl;
	}
	if (type == "G" || type == "g") {
		strat = new GreedyPlayer();
		cout << lastName << " is a greedy player" << endl;
		lastName += " (Greedy)";
		cout << endl << endl;
	}
	if (type == "M" || type == "m"){
		strat = new ModeratePlayer();
		cout << lastName << " is a moderate player" << endl;
		lastName += " (Moderate)";
		cout << endl << endl;
	}
	if (type == "H" || type == "h"){
		strat = new HumanPlayer();
		cout << lastName << " is a human player" << endl;
		lastName += " (Human)";
		cout << endl << endl;
	}
	strat->SetPlayer(this);
}

//**********
//InitializePlayerForTournament
//**********
void Player::InitializePlayerForTournament(int pos) {
	bool isValidInput = false;
	char type;
	for (int i = 0; i < STARTING_ARMIES; i++) {
		cubes.push_back(new Cube());
		cubes[i]->isPlaced = false;
	}
	for (int j = 0; j < STARTING_ARMIES; j++)
		disks.push_back(new Disk());
	if (MasterGame->playerCount == 2 && pos == 2)
		return;
	cout << "Enter the name of Player " << pos + 1 << ": ";
	cin >> lastName;
	while (isValidInput == false) {
		cout << endl << lastName << " is what kind of player are you?" << endl;
		cout << "(G) Greedy" << endl;
		cout << "(M) Moderate" << endl;
		cin >> type;
		if (cin.fail()) {
			cout << "Invalid input, please try again" << endl;
		}
		else {
			switch (type) {
			case 'G':
			case 'g':
				strat = new GreedyPlayer();
				cout << lastName << " is a greedy player" << endl;
				lastName += " (Greedy)";
				cout << endl << endl;
				isValidInput = true;
				break;
			case 'M':
			case 'm':
				strat = new ModeratePlayer();
				cout << lastName << " is a moderate player" << endl;
				lastName += " (Moderate)";
				cout << endl << endl;
				isValidInput = true;
				break;
			default:
				cout << "Invalid input, please try again" << endl;
			}
		}
	}
	strat->SetPlayer(this);
}
