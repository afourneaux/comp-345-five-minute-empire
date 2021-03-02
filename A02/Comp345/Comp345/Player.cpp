#include "Player.h"
#include<iostream>
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
	cout << lastName << " is is trying to pay " << amt << " coins..." << endl;
	if (coins - amt >= 0) {
		cout << "Great, you do have enough coins. You currently have " << coins << " coins." << endl;
		coins -= amt;
		enoughCoins = true;
	}
	else {
		cout << "Sorry, you do not have enough coins. You currently have " << coins << " coins." << endl;
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
	int terr;
	Territory* dest = nullptr;
	if (!HasArmiesToPlace()) return hasPlaced;
	while (!hasPlaced) {
		cout << lastName << " - Where would you like to " << "place a new army" << " (ID)? (-1 to exit): ";
		cin >> terr;
		dest = HasCityAtLocation(terr);
		if (terr == STARTING_REGION_ID || dest != nullptr && dest->city_count[pos] > 0) { // Checking if destination has a city of player or is starting region
			dest->addArmy(pos);
			hasPlaced = true;
		}
	}
	return hasPlaced;
}
//**********
//MoveArmies
//**********
bool Player::MoveArmies() {
	bool hasMoved = false;
	Territory* src = PromptForAction("move army from");
	if (src == nullptr) return hasMoved; // if user exits action
	Territory* dest = PromptForAction("move army to");
	if (dest == nullptr) return hasMoved; // if user exits action
	src->removeArmy(pos);
	dest->addArmy(pos);
	return hasMoved;
}
//**********
//MoveOverLand
//**********
bool Player::MoveOverLand() {
	bool hasMoved = false;
	Territory* src = PromptForAction("move army over land from");
	if (src == nullptr) return hasMoved; // if user exits action
	Territory* dest = PromptForAction("move army over land to");
	if (dest == nullptr) return hasMoved; // if user exits action
	src->removeArmy(pos);
	dest->addArmy(pos);
	return hasMoved;
}
//**********
//BuildCity
//**********
bool Player::BuildCity() {
	bool isCityBuilt = false;
	bool hasCity = false;
	bool hasArmy = false;
	Disk* city = nullptr;
	Territory* settlement = PromptForAction("build a city");
	if (settlement == nullptr) return isCityBuilt; // if user exits action
	for (int i = 0; i < 3; i++) {  // Check if player has a city to build
		if (!disks[i]->isBuilt) {
			city = disks[i];
			hasCity = true;
			cout << lastName << " - You DO have atleast one city available for building at location ID: " << settlement->territoryID << "." << endl;
		}
		else {
			cout << lastName << " - You DO NOT have atleast one city available for buildingat location ID: " << settlement->territoryID << "." << endl;
			return false;
		}
	}
	for (int j = 0; j < cubes.size(); j++) // Check if player has army at location
		if (cubes[j]->location == settlement) {
			hasArmy = true;
			cout << lastName << " - You DO have atleast one city at location ID: " << settlement->territoryID << "." << endl;
		}
			
		else {
			cout << lastName << " - You DO NOT have atleast one army at location ID: " << settlement->territoryID << "." << endl;
			return false;
		}
	if (hasArmy && hasCity) { // Check if above conditions are met
		city->location = settlement;
		city->isBuilt = true;
		isCityBuilt = true;
		cout << lastName << " - Successfully built a city at territory ID: " << settlement << "." << endl;
	}
	else
		cout << lastName << " - Failed to build a city at territory ID: " << settlement << "." << endl;
	return isCityBuilt;
}

//Checks if friendly & ennemy in same location -> Returns if it was destroyed
bool Player::DestroyArmy() {
	bool isDestoyed = false;
	int ennemy = -1;
	bool ennemyfound = false;
	Territory* battlefield = PromptForAction("destroy an ennemy army");
	if (battlefield == nullptr) return isDestoyed; // if user exits action
	while (!ennemyfound) {
		cout << lastName << " - Who's army would you like to destroy (pos)? " << endl;
		cin >> ennemy;
		if (battlefield->army_count[ennemy] > 0) {
			ennemyfound = true;
			battlefield->removeArmy(ennemy); 
			isDestoyed = true;
		}
	}
	return isDestoyed;
}
//****************************************************************************************************************************************************************************
//                                                                 HELPER METHODS
//****************************************************************************************************************************************************************************

//**********
//DoAction
//**********
bool Player::DoAction(Card* card) {
	bool hasActed = false;
	for (int i = 0; i < card->abilityCount; i++) {
		switch (card->actions[i].action) {
		case eAction_BuildCity: if (BuildCity()) hasActed = true;
				break;
		case eAction_DestroyArmies: if (DestroyArmy()) hasActed = true;
				break;
		case eAction_MoveArmies: if (MoveArmies()) hasActed = true;
				break;
		case eAction_PlaceArmies: if (PlaceNewArmies()) hasActed = true;
				break;
		default:
			cout << "Found an invalid action for card name:" << card->name;
			break;
		}
	}
	return hasActed;
}
//**********
//PromptForAction
//**********
Territory* Player::PromptForAction(string action) {
	PlayerStatus();
	int terrId = -1;
	bool exit = false; // set to true to exit loop
	while (HasArmyAtLocation(terrId) == nullptr && !exit) {
		cout << lastName << " - Where would you like to " << action << " (ID)? (-1 to exit): ";
		cin >> terrId;
		if (terrId == -1) {
			exit = true;
			cout << lastName << " - Did not take any actions." << endl;
		}
	}
	return HasArmyAtLocation(terrId);
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
		cout << "Territory Id " << terr->territoryID << " has currently " << terr->army_count[pos] << " unit(s) of army and " << terr->city_count[pos] << " unit(s) of city" << endl;
	}
	cout << lastName << " - End Statistics." << endl;
}
//**********
//HasArmyAtLocation
//**********
Territory* Player::HasArmyAtLocation(int id) {
	for (int i = 0; i < GetTerritories().size(); i++) {
		for (int j = 0; j < cubes.size(); j++)
			if (cubes[j]->location->territoryID == id) {
			cout << lastName << "- You currently have " << cubes[j]->location->army_count[pos] << " army unit(s) at territory id " << id << "." << endl;
			return cubes[j]->location;
		}
	}
	return nullptr;
}
//**********
//HasCityAtLocation
//**********
Territory* Player::HasCityAtLocation(int id) {
	for (int i = 0; i < GetTerritories().size(); i++) {
		for (int j=0; j<disks.size(); j++)
			if (disks[j]->location->territoryID == id) {
			cout << lastName << "- You currently have " << disks[j]->location->city_count[pos] << " city unit(s) at territory id " << id << "." << endl;
			return cubes[j]->location;
		}
	}
	return nullptr;
}
//**********
//HasArmyToPlace
//**********
bool Player::HasArmiesToPlace() {
	for (int i = 0; i < cubes.size(); i++) {
		if (!cubes[i]->isPlaced)
			return true;
	}
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




