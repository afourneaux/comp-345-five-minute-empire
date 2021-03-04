#include<iostream>
#include "Game.h"
using namespace std;


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
ostream& operator<<(ostream& out, const Player &player) {
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
bool Player::PayCoin(int amt) {
	bool enoughCoins = false;
	cout << lastName << " is trying to pay " << amt << " coins..." << endl;
	if (coins - amt >= 0) {
		cout << lastName << " - You DO have enough coins. You currently have " << coins << " coins." << endl;
		coins -= amt;
		enoughCoins = true;
	}
	else {
		cout << lastName << " - You DO NOT have enough coins. You currently have " << coins << " coins." << endl;
		enoughCoins = false;
	}
	cout << lastName << " now has " << coins << " coins." << endl;
	return enoughCoins;
}
//**********
//PlaceNewArmies
//**********
bool Player::PlaceNewArmies() {
	bool hasPlaced = false;
	int dest;
	Territory* destination;
	while (!hasPlaced) {
		if (!HasArmiesToPlace()) return hasPlaced;
		cout << lastName << " - Where would you like to place a new army (ID)? (-1 to skip action) ";
		cin >> dest;
		if (dest == -1)
			return false;
		if (dest == STARTING_REGION_ID)
			destination = GetTerritory(STARTING_REGION_ID);
		else
			destination = GetTerritory(dest);
		if (dest == STARTING_REGION_ID || destination->city_count[position] > 0) { // Checking if destination has a city of player or is starting region
			for (int i = 0; i < cubes.size(); i++) { // check if have available armies and places it if it does
				if (!cubes[i]->isPlaced) {
					cubes[i]->isPlaced = true;
					cubes[i]->location = destination;
					hasPlaced = true;
					UpdateTerritory(destination); // Updating player territories
					destination->addArmy(position); // Updating map territories
					return hasPlaced;
				}
			}
		}
		else
			cout << lastName << " - You cannot place an army at " << dest << "." << endl;
	}
	return hasPlaced;
}
//**********
//MoveArmies
//**********
bool Player::MoveArmies() {
	bool hasMoved = false;
	int src, dest;
	bool exit = false;
	while (!hasMoved) {
		cout << lastName << " - Where would you like to move an army FROM (ID)? (-1 to skip action)" << endl;
		cin >> src;
		if (src == -1) 
			return false;
		Territory* source = GetTerritory(src);
		cout << lastName << " - Where would you like to move an army TO (ID)? (-1 to skip action)" << endl;
		cin >> dest;
		Territory* destination = GetTerritory(dest);
		Cube* army = HasArmyAtLocation(src);
		if (army!= nullptr && source->CheckAdjacency(destination)) {
			army->location = destination; 
			UpdateTerritory(destination); // Updating Player
			source->removeArmy(position); // Updating Map
			destination->addArmy(position); // Updating Map
			hasMoved = true;
			//Update map
		}
	}
	return hasMoved;
}
//**********
//MoveOverLand
//**********
bool Player::MoveOverLand() {
	bool hasMoved = false;
	int src, dest;
	while (!hasMoved) {
		cout << lastName << " - Where would you like to move an army FROM (ID)? (-1 to skip action)" << endl;
		cin >> src;
		if (src == -1) 
			return false;
		Territory* source = GetTerritory(src);
		cout << lastName << " - Where would you like to move an army TO (ID)? (-1 to skip action)" << endl;
		cin >> dest;
		if (dest == -1) 
			return false;
		Territory* destination = GetTerritory(dest);
		Cube* army = HasArmyAtLocation(src);
		if (army != nullptr && source->CheckAdjacency(destination)) {
			army->location = destination;
			UpdateTerritory(army->location); // Updating Player
			source->removeArmy(position); // Updating Map
			destination->addArmy(position); // Updating Map
			hasMoved = true;
		}
	}
	return hasMoved;
}
//**********
//BuildCity
//**********
bool Player::BuildCity() {
	bool isBuilt = false;
	bool hasCity = false;
	bool hasArmy = false;
	Disk* city = nullptr;
	int id;
	while (!isBuilt) {
		cout << lastName << " - Where would you like to build a city (ID)? (-1 to skip action) ";
		cin >> id;
		if ( id == -1) 
			return false;
		Territory* city_terr = GetTerritory(id);
		if (city_terr == nullptr) continue;
		if (HasCitiesToPlace()) 
			hasCity = true;
		if (HasArmyAtLocation(id) != nullptr || id == STARTING_REGION_ID)
			hasArmy = true;
		if (hasArmy && hasCity) { // Check if above conditions are met
			city = HasCitiesToPlace();
			city->location = city_terr;
			city->isBuilt = true;
			isBuilt = true;
			UpdateTerritory(city->location); // Updating Player
			city->location->addCity(position); // Updating Map
			cout << lastName << " - Successfully built a city at territory ID: " << city->location->territoryID << "." << endl;
		}
		else
			cout << lastName << " - Failed to build a city at territory ID: " << id << "." << endl;
	}

	return isBuilt;
}

bool Player::DestroyArmy() {//Checks if friendly & ennemy in same location -> Returns if it was destroyed
	int ennemy, battle_terr_id = -1;
	bool isDestoyed = false;
	Territory* battlefield_terr = nullptr;
	while (!isDestoyed) {
		cout << lastName << " - Where would you like to attack (id) (-1 to skip action)? ";
		cin >> battle_terr_id;
		if (battle_terr_id == -1) 
			return false;
			cout << lastName << " - Who's army would you like to destroy (position)? ";
			cin >> ennemy;
			battlefield_terr = GetTerritory(battle_terr_id);
			if (HasArmyAtLocation(battle_terr_id) == nullptr) continue;
			if (battlefield_terr == nullptr) continue;
			if (ennemy < 0 || ennemy >= NUM_OF_PLAYERS) continue;
			if (battlefield_terr->army_count[ennemy] > 0 && battlefield_terr->army_count[position] > 0) {
				for (int i = 0; i < Game::players[ennemy]->getCubes().size(); i++) {
					if (Game::players[ennemy]->getCubes()[i]->location == battlefield_terr) {
						Game::players[ennemy]->getCubes()[i]->location = nullptr;
						Game::players[ennemy]->getCubes()[i]->isPlaced = false;
						cout << Game::players[0]->lastName << " - Army destroyed and now has "  << endl;
						UpdateTerritory(battlefield_terr); // Updating Player
						battlefield_terr->removeArmy(ennemy); // Updating Map
						isDestoyed = true;
						break;
					}
				}
			}
	}
	return isDestoyed;
}
int Player::AndOrAction() {
	Card* currentCard = hand.back();
	int choice = -1;
	string and_or;
	if (currentCard->actionChoice == 1)
		and_or = "AND";
	if (currentCard->actionChoice == 2)
		and_or = "OR";
	cout << lastName << " - The card you have choosen allows you to " << currentCard->actions[0] << " " << and_or << " " << currentCard->actions[1] << endl;
	if (currentCard->actionChoice == eChoice_Or) {
		cout << lastName << " - Since you have the OR card, please choose: " << endl;
		cout << "Press 0: " << currentCard->actions[0] << endl;
		cout << "Press 1: " << currentCard->actions[1] << endl;
		cin >> choice;
	}
	return choice;
}
//****************************************************************************************************************************************************************************
//                                                                 HELPER METHODS
//****************************************************************************************************************************************************************************

//**********
//DoAction
//**********
bool Player::DoAction(Card* card) {
	bool hasActed = false;
	int action = 0;
	int possibleactions = 2;
	hand.push_back(card);
	switch (AndOrAction()) {
	case 0:
		action = 0;
		possibleactions = 1;
		break;
	case 1:
		action = 1;
		possibleactions = 2;
		break;
	default:
		action = 0;
		possibleactions = card->actionCount;
	}
for (action = 0; action < possibleactions; action++) {
		for (int i = 0; i < card->actions[action].actionValue; i++) {
			switch (card->actions[action].action) {
			case eAction_BuildCity: BuildCity();
				break;
			case eAction_DestroyArmies: DestroyArmy();
				break;
			case eAction_MoveArmies: MoveArmies();
				break;
			case eAction_PlaceArmies: PlaceNewArmies();
				break;
			default:
				cout << "Found an invalid action for card name:" << card->name;
				break;
			}
		}
	}
	return hasActed;
}
//**********
//PlayerStatus
//**********
void Player::PlayerStatus() {
	vector <Territory*> territories = GetTerritories();
	Territory* terr = nullptr;
	cout << lastName << " - Start Statistics:" << endl;
	for (int i=0; i<territories.size(); i++) {
		 terr = territories[i];
		cout << "Territory Id " << terr->territoryID << " has currently " << terr->army_count[position] << " unit(s) of army and " << terr->city_count[position] << " unit(s) of city" << endl;
	}
	cout << lastName << " - End Statistics." << endl;
}
//**********
//HasArmyAtLocation
//**********
Cube* Player::HasArmyAtLocation(int id) {
		for (int i = 0; i< cubes.size(); i++)
			if (cubes[i]->location != nullptr && cubes[i]->location->territoryID == id)
				return cubes[i];
	return nullptr;
}
//**********
//HasArmyAtLocation
//**********
Disk* Player::HasCityAtLocation(int id) {
	for (int i = 0; i < disks.size(); i++)
		if (disks[i]->location->territoryID == id) return disks[i];
	return nullptr;
}
Territory* Player::GetTerritory(int id) {
	return Game::map->GetTerritory(id);
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
//UpdateTerritory
//**********
void Player::UpdateTerritory(Territory* terr) {
	if (!Find(terr))
		territories.push_back(terr);
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
////**********
////AddArmy
////**********
//bool Player::AddArmy(int player_idx, Territory* terr) {
//	vector <Cube*> cubes = players.at(player_idx)->getCubes();
//	for (int i = 0; i < cubes.size(); i++) {
//		if (!cubes[i]->isPlaced) {
//			cubes[i]->location = terr;
//			cubes[i]->isPlaced = true;
//		}
//	}
//}
////**********
////RemoveArmy
////**********
//bool Player::RemoveArmy(int player_idx, Territory* terr) {
//	vector <Cube*> cubes = players.at(player_idx)->getCubes();
//	for (int i = 0; i < cubes.size(); i++) {
//		if (cubes[i]->location == terr) {
//			cubes[i]->location = nullptr;
//			cubes[i]->isPlaced = false;
//		}
//	}
//}
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




