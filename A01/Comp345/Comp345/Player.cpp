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
	//iterate through armies
	for (int i = 0; i < cubes.size(); i++)
		delete cubes[i];
	//iterat trough disks
	for (int i = 0; i < disks.size(); i++)
		delete disks[i];
	//iterate through hand
	for (int i = 0; i < hand.size(); i++)
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
	bf = player->getBf(); //Need copy constructor of Bf
	lastName = player->getLastName();
	//Copying territories
	for (int i = 0; i < player->getTerritories().size(); i++) {
		territories[i]->army_count = player->getTerritories()[i]->army_count;
		territories[i]->city_count = player->getTerritories()[i]->city_count;
		territories[i]->continentID = player->getTerritories()[i]->continentID;
		territories[i]->head = player->getTerritories()[i]->head;
		territories[i]->territoryID = player->getTerritories()[i]->territoryID;
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
	bf = player.getBf(); //Need copy constructor of Bf
	lastName = player.getLastName();
	//Copying territories
	for (int i = 0; i < player.getTerritories().size(); i++) {
		territories[i]->army_count = player.getTerritories()[i]->army_count;
		territories[i]->city_count = player.getTerritories()[i]->city_count;
		territories[i]->continentID = player.getTerritories()[i]->continentID;
		territories[i]->head = player.getTerritories()[i]->head;
		territories[i]->territoryID = player.getTerritories()[i]->territoryID;
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
//Loops through all armies and if not placed -> Assigns it a territory
bool Player::PlaceNewArmies(Territory* dest) {
	bool placed = false;
	if (dest == nullptr)
		return false;
	for (int i = 0; i < cubes.size(); i++) {
		if (!cubes[i]->isPlaced) {
			cubes[i]->location = dest;
			cubes[i]->isPlaced = true;
			placed = true;
			armiesLeft--;
			break;
		}
	}
	if (armiesLeft > 0)
		cout << lastName << ", successfully put an Army at territoryID: " << dest->territoryID << " and has " << armiesLeft << " armies left." << endl;
	else
		cout << "You do not have any more armies to place." << endl;
	return placed;
}
//Loops through all armies in a territory -> Assigns it a new territory (calculation for movement imissing)
bool Player::MoveArmies(Territory* src, Territory* dest) {
	bool placed = false;
	if (src == nullptr || dest == nullptr)
		return placed;
	for (int i = 0; i < getCubes().size(); i++) {
		if (cubes[i]->location == nullptr)
			continue;
		if (cubes[i]->location->territoryID == src->territoryID) {
			cubes[i]->location = dest;
			placed = true;
			cout << "Successfully moved Army from ID: " << src->territoryID << " to ID: " << dest->territoryID << endl;
			//Todo: Need to remove amount of moves based on territoryID
			return placed;
		}
	}
	cout << lastName << ", you cannot make the move, you currently have no armies at ID: " << src->territoryID << "." << endl;
	return placed;
}
//Loops through all armies in a territory -> Assigns it a new territory (calculation for movement imissing)
bool Player::MoveOverLand(Territory* src, Territory* dest) {
	bool placed = false;
	if (src == nullptr || dest == nullptr)
		return placed;
	for (int i = 0; i < getCubes().size(); i++) {
		if (cubes[i]->location == nullptr)
			continue;
		if (cubes[i]->location->territoryID == src->territoryID) {
			cubes[i]->location = dest;
			placed = true;
			cout << "Successfully moved army over land from ID: " << src->territoryID << " to ID: " << dest->territoryID << endl;
			//Todo: Need to remove amount of moves based on territoryID
			return placed;
		}
	}
	cout << lastName << ", you cannot make the move, you currently have no armies at ID: " << src->territoryID << "." << endl;
	return placed;
}
//Returns true if player has a city to build && has an army at the destination
bool Player::BuildCity(Territory* dest) {
	bool isCityBuilt = false;
	bool hasCity = false;
	bool hasArmy = false;
	Disk* city = nullptr;
	//Check if player has a city to build
	for (int i = 0; i < 3; i++) {
		if (!disks[i]->isBuilt) {
			city = disks[i];
			hasCity = true;
		}
	}
	cout << endl;
	//Check if player has army at location
	for (int j = 0; j < cubes.size(); j++)
		if (cubes[j]->location != nullptr && cubes[j]->location->territoryID == dest->territoryID)
			hasArmy = true;

	if (hasCity)
		cout << lastName << " has a city to build." << endl;
	else
		cout << lastName << " does not have a city to build." << endl;
	if (hasArmy)
		cout << lastName << " has an army at territory ID: " << dest->territoryID << "." << endl;
	else
		cout << lastName << " does not have an army at territory ID: " << dest->territoryID << "." << endl;

	//Check if above conditions are met
	if (hasArmy && city != nullptr) {
		city->location = dest;
		city->isBuilt = true;
		isCityBuilt = true;
		cout << "->" << lastName << " built a city at territory ID: " << dest->territoryID << "." << endl;
	}
	else
		cout << "->" << lastName << " did not build a city at territory ID: " << dest->territoryID << "." << endl;
	return isCityBuilt;
}

//Checks if friendly & ennemy in same location -> Returns if it was destroyed
bool Player::DestroyArmy(Territory* friendlyTerr, Territory* ennemyTerr, Player *ennemy) {
	bool isDestoyed = false;
	for (int i = 0; i < cubes.size(); i++) {
		if (friendlyTerr == cubes[i]->location && cubes[i]->location->territoryID == ennemyTerr->territoryID) {
			for (int j = 0; j < ennemy->getCubes().size(); j++) {
				if (ennemy->getCubes()[j]->location == nullptr)
					continue;
				if (ennemy->getCubes()[j]->location->territoryID == ennemyTerr->territoryID) {
					ennemy->getCubes()[j]->isPlaced = false;
					ennemy->getCubes()[j]->location = nullptr;
					isDestoyed = true;
				}
			}
		}
	}
	if (isDestoyed)
		cout << lastName << " destroyed his enemy " << ennemy->lastName << " at " << ennemyTerr->territoryID << " with his army at " << friendlyTerr->territoryID << "." << endl;
	else
		cout << lastName << " could not defeat his enemy " << ennemy->lastName << " at " << ennemyTerr->territoryID << ", with his army is at " << friendlyTerr->territoryID << endl;
	return isDestoyed;
}

void Player::InitializePlayer() {
	for (int i = 0; i < 18; i++) {
		cubes.push_back(new Cube());
		cubes[i]->isPlaced = false;
	}
	for (int j = 0; j < 3; j++)
		disks.push_back(new Disk());
}




