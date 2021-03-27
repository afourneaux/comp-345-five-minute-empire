#include<iostream>
#include <algorithm>
#include "Game.h"

using namespace std;

extern Game* MasterGame;

Player::Player()
{
	InitializePlayer();
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
	for (int i = 0; i < player->getCubes().size(); i++) {
		cubes[i]->isPlaced = player->getCubes()[i]->isPlaced;
		cubes[i]->location = player->getCubes()[i]->location;
	}
	//Copying disks
	for (int i = 0; i < player->getDisks().size(); i++) {
		disks[i]->isBuilt = player->getDisks()[i]->isBuilt;
		disks[i]->location = player->getDisks()[i]->location;
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
	for (int i = 0; i < player.getCubes().size(); i++) {
		cubes[i]->isPlaced = player.getCubes()[i]->isPlaced;
		cubes[i]->location = player.getCubes()[i]->location;
	}
	//Copying disks
	for (int i = 0; i < player.getDisks().size(); i++) {
		disks[i]->isBuilt = player.getDisks()[i]->isBuilt;
		disks[i]->location = player.getDisks()[i]->location;
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
	out << "Coins: " << player.getCoins() << endl;
	//Army locations
	out << "Armies locations: " << endl;
	for (int i = 0; i < player.getCubes().size(); i++)
		if (player.getCubes()[i]->isPlaced)
			cout << "ID: " << player.getCubes()[i]->location->territoryID << endl;
	out << endl;
	//Cities locations
	out << "Disks locations: " << endl;
	for (int i = 0; i < player.getDisks().size(); i++)
		if (player.getDisks()[i]->isBuilt)
			cout << "ID: " << player.getDisks()[i]->location->territoryID << endl;
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
	Cube* cube;
	Territory* destination = nullptr;
	while (true) {
		if (!HasArmiesToPlace()) {
			cout << "SORRY, cannot perform action (No armies to place) " << endl;
			PrintPlacedArmies();
			return COST_ONE_ACTIONVALUE;
		}
		cout << "Here are VALID inputs: " << endl;
		cout << "-> Territory ID (Starting Region): " << MasterGame->map->starting_territory_index << endl;
		PrintPlacedCities();
		cube = GetRandomArmy();
		cout << lastName << " - PLACE NEW ARMY (-1 to skip): " ;
		cin >> dest;
		if (HasSkipped(dest)) return COST_ONE_ACTIONVALUE;
		if (GetTerritory(dest) == nullptr) continue;
		destination = GetTerritory(dest);
		if (dest == MasterGame->map->starting_territory_index || destination->city_count[position] > 0) {		
			destination = GetTerritory(dest);	
			AddArmy(destination, cube);				
			return COST_ONE_ACTIONVALUE;
		}
		else {									
			cout << endl << "WARNING - You cannot place an army at territory ID. " << dest << ". " << endl;
		}
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
	int movementCost = 0;
	int landOrSea;
	int src, dest;
	bool exit = false;
	if (!HasArmiesOnBoard()) {
		cout << "SORRY, cannot perform action (No armies to move)" << endl;
		PrintPlacedArmies();
		return COST_ONE_ACTIONVALUE;
	}
	while (true) {
		cout << "Here are VALID inputs: " << endl;
		PrintPlacedArmies();
		cout << lastName << " - MOVE FROM (-1 to skip): ";
		cin >> src;
		if (HasSkipped(src)) return COST_ONE_ACTIONVALUE;
		if (!HasArmyAtLocation(src)) {
			cout << endl << "WARNING - You do not have any armies at territory ID: " << src << endl;
			continue;
		}
		Territory* source = GetTerritory(src);
		cout << lastName << " - MOVE TO (-1 to skip): ";
		cin >> dest;
		if (HasSkipped(dest)) return COST_ONE_ACTIONVALUE;
		if (GetTerritory(dest) == nullptr) continue;
		Territory* destination = GetTerritory(dest);
		Cube* srcArmy = GetArmyAtLocation(src);
		movementCost = MasterGame->map->GetMovementCost(src, dest, bonusFlying);
		if (movementCost <= numOfMoves && movementCost > 0){
			cout << "This move will cost " << movementCost << " move(s). Do you wish to continue? (Y/N) ";
			string ans;
			cin >> ans;
			if (ans == "N" || ans == "n")
				continue;
			else if (ans == "Y" || ans == "y") {
				srcArmy->location = destination;
				cout << "Moved army from location " << src << " to destination " << dest << endl;
				source->removeArmy(position);						// Updating Map
				destination->addArmy(position);						// Updating Map
				if (!Find(destination))								// Updating Player territories
					territories.push_back(destination);
				for (int i = 0; i < territories.size(); i++) {		// Updating Player territories
					if (territories[i] == source && source->army_count[position] == 0 && source->city_count[position] == 0)
						territories.erase(territories.begin() + i);
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
//**********
//MoveOverLand
//**********
bool Player::MoveOverLand() {
	return true;
}
//**********
//BuildCity
//**********
int Player::BuildCity() {
	Disk* city;
	int dest;
	if (!HasArmiesOnBoard()) {
		cout << "Put some armies first, jeez!" << endl;
		return COST_ONE_ACTIONVALUE;
	}
	if (!HasCitiesToPlace()) {
		cout << "Are you trying to become a real estate agent o.O? I think not." << endl;
		PrintPlacedCities();
		return COST_ONE_ACTIONVALUE;
	}
	cout << endl;
	for (int i = 0; i < disks.size(); i++)
		if (!disks[i]->isBuilt) {
			city = disks[i];
			break;
		}
	while (true) {
		cout << "Here are VALID inputs: " << endl;
		PrintPlacedArmies();
		cout << lastName << " - BUILD CITY AT (-1 to skip): " << endl;
		cin >> dest;
		if (HasSkipped(dest)) return COST_ONE_ACTIONVALUE;
		if (GetTerritory(dest) == nullptr) continue;
		if (HasArmyAtLocation(dest)) {
			AddCity(GetTerritory(dest));
			return COST_ONE_ACTIONVALUE;
		}
		else
			cout << "Don't you dare try to build a city at "<< dest <<"! You have no armies there! " << dest << "." << endl;
	}
}

int Player::DestroyArmy() {//Checks if friendly & enemy in same location -> Returns if it was destroyed
	int enemy, battlefieldTerrId;
	Territory* battlefieldTerr = nullptr;
	if (!HasArmiesOnBoard()) {
		cout << "Attacking with no armies... Pathetic..." << endl;
		PrintPlacedArmies();
		return COST_ZERO_ACTIONVALUE;
	}
	while (true) {
		cout << "Here are VALID inputs: " << endl;
		PrintPlacedArmies();
		cout << lastName << " - DESTROY AT (-1 to skip)? ";
		cin >> battlefieldTerrId;
		if (HasSkipped(battlefieldTerrId)) return COST_ONE_ACTIONVALUE;
		if (GetTerritory(battlefieldTerrId) == nullptr) continue;
		if (!HasArmyAtLocation(battlefieldTerrId)) {
			cout << endl << "There is nobody at " << battlefieldTerrId << "to fight for you! Think again." << endl;
			continue;
		}
		battlefieldTerr = GetTerritory(battlefieldTerrId);
		for (int i = 0; i < GetTerritory(battlefieldTerrId)->army_count.size(); i++)
			cout << MasterGame->players[i]->lastName << " at pos " << MasterGame->players[i]->position << " has " << GetTerritory(battlefieldTerrId)->army_count[i] << " armies at your location" << endl;
		cout << lastName << " - DESTROY WHOM (-1 to skip): " << endl;
		cin >> enemy;
		if (HasSkipped(battlefieldTerrId)) return COST_ONE_ACTIONVALUE; // Check if wants to skip action
		if (enemy < 0 || enemy >= MasterGame->players.size()) { // Checking if valid player position
			cout << "Might as well attack the chair! Find a real opponent." << endl << endl;
			continue;
		}
		if (enemy == position) {
			cout << "Feel free to punch yourself in real life but not happening in my game!" << endl << endl;
			continue;
		}
		if (MasterGame->players[enemy]->bonusImmune) {
			cout << "You can't attack " << enemy << " because they have the 'Immune to Attack' bonus. Please choose a different target." << endl;
			continue;
		}
		if (battlefieldTerr->army_count[enemy] <= 0) { // Checking if ennemy has armies
			cout << "Now you are attacking straight wind. " << enemy << " does not have anything at " << battlefieldTerr->territoryID << " to destroy. " << endl << endl;
			continue;
		}
		MasterGame->players[enemy]->RemoveArmy(battlefieldTerr); // Destroying Army
		cout << "BANG BANG. You shot him down, BANG BANG. " << MasterGame->players[enemy]->lastName << " hit the gound. BANG bang ...(at territory id " << battlefieldTerrId << ") That awful sound.." << endl;
		MasterGame->players[enemy]->PrintPlayerStatus();
		return COST_ONE_ACTIONVALUE;
	}
}
//**********
//DoAction
//**********
void Player::DoAction(Card* card) {
	int receivedCoins;
	bool hasActed = false;
	int possibleActions = 0, cost = 0, receivedCoins = 0;
	hand.push_back(card);						// puts drawn card in the hand of player
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
		}
	}

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
}
int Player::ComputeScore() {

	//Calculate the scores for controlled continents + territories
	int mapScore = MasterGame->map->ComputeMapScore(position);
	int score = 0;
	int player_count = MasterGame->players.size();

	int* elixir_count = new int[player_count];
	for (int i = 0; i < player_count; i++) elixir_count[i] = 0;

	//Loop through each player
	for (int player_index = 0; player_index < player_count; player_index++) {
		Player* player = MasterGame->players[player_index];
		vector<Card*> playerHand = player->getHand();
		//Loop through each card player owns
		for (int card_index = 0; card_index < playerHand.size(); card_index++) {
			//loop through each ability on each card
			for (int ability_index = 0; ability_index < playerHand[card_index]->abilityCount; ability_index++) {
				Ability* ability = &playerHand[card_index]->abilities[ability_index];
				//count the number of elixirs each player owns
				if (ability->type == eAbility_Elixir) {
					if (player == this) cout << "Card " << playerHand[card_index]->name << " has " << ability->value << " Elixirs" << endl;
					elixir_count[player_index] += ability->value;
				}
				//If the player iteration matches the calling player, compute scores from other points-giving cards
				if (player == this) {
					//If the card grants VP per cardName, count the number of cards with that name
					if (ability->type == eAbility_VpPerCardName) {
						cout << "Card " << playerHand[card_index]->name << " grants VP for " << ability->setName << " Cards" << endl;
						int count = 0;
						for (int i = 0; i < playerHand.size(); i++) {
							if (playerHand[i]->name.find(ability->setName) != string::npos) {
								cout << "Found " << ability->setName << " Card: " << playerHand[i]->name << endl;;
								count++;
							}
						}
						if (count >= ability->setTarget) {
							if (ability->countSetOnce)
								score += ability->value;
							else
								score += ability->value * count;
						}
					}
					else if (ability->type == eAbility_VpPerCoins) {
						cout << "Card " << playerHand[card_index]->name << " grants 1 VP per " << ability->setTarget << " Coins" << endl;
						cout << "Bonus from coins: " << (coins / ability->setTarget) * ability->value << endl;
						score += (coins / ability->setTarget) * ability->value;
					}
					else if (ability->type == eAbility_VpPerFlying) {
						cout << "Card " << playerHand[card_index]->name << " grants VP for flying cards" << endl;
						int count = 0;
						for (int i = 0; i < playerHand.size(); i++) {
							for (int j = 0; j < playerHand[i]->abilityCount; j++) {
								if (playerHand[i]->abilities[j].type == eAbility_Flying) {
									count++;
									cout << "Found flying card: " << playerHand[i]->name << endl;;
								}
							}
						}
						score += ability->value * count;
					}
				}
			}
		}
	}
	cout << lastName << " has " << elixir_count[position] << " Elixirs." << endl;
	int elixir_winner = -1;
	int elixir_max = -1;
	for (int i = 0; i < player_count; i++) {
		if (elixir_count[i] > elixir_max) {
			elixir_winner = i;
			elixir_max = elixir_count[i];
		}
		else if (elixir_count[i] == elixir_max) {
			elixir_winner = -1;
		}
	}
	if (elixir_winner == position) {
		cout << "Player " << lastName << " has the most elixirs, gets " << ELIXIR_BONUS << " bonus points." << endl;
		score += ELIXIR_BONUS;
	}

	int final_score = score + mapScore;
	cout << endl << "FINAL SCORE FOR PLAYER " << lastName << ": " << final_score << endl << endl;

	delete[] elixir_count;
	return final_score;
}

void Player::AddCardToHand(Card* card) {
	hand.push_back(card);
}

//****************************************************************************************************************************************************************************
//                                                                 HELPER METHODS
//****************************************************************************************************************************************************************************

// if OR -> Returns 0 or 1 depending on user inputs which is the action choosen. If AND -> Returns -1 is because we have an AND action
int Player::AndOrAction() {
	Card* currentCard = hand.back(); //Last drawn card
	int choice = -1;
	string and_or;
	if (currentCard->actionChoice == eChoice_And) // For nice output
		and_or = "AND";
	if (currentCard->actionChoice == eChoice_Or) // For nice output
		and_or = "OR";
	if (currentCard->actionChoice == eChoice_None) // For nice output
		and_or = "";
	cout << lastName << " - The card you have chosen allows you to " << currentCard->actions[0] << " " << and_or << " " << currentCard->actions[1] << endl;
	PrintPlayerStatus();
	if (currentCard->actionChoice == eChoice_Or) {
		cout << lastName << " - Since you have the OR card, please choose: " << endl;
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
//**********
//PrintPrintPlayerStatus
//**********
void Player::PrintPlayerStatus() {
	vector <Territory*> territories = GetTerritories();
	Territory* terr = nullptr;
	cout << ">>>>" << endl;
	cout << endl << lastName << " control statistics:" << endl;
	for (int i = 0; i < territories.size(); i++) {
		terr = territories[i];
		cout << "Territory ID " << terr->territoryID << ": " << terr->army_count[position] << " cube(s) & " << terr->city_count[position] << " disk(s) " << endl;
	}
	cout << "<<<<" << endl;
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
void Player::InitializePlayer() {
	for (int i = 0; i < 18; i++) {
		cubes.push_back(new Cube());
		cubes[i]->isPlaced = false;
	}
	for (int j = 0; j < 3; j++)
		disks.push_back(new Disk());
}




