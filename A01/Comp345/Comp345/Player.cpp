#include "Player.h"
#include<iostream>
using namespace std;

Player::Player()
{
	InitializePlayer();
	this->bf = new BidingFacility();
}
Player::~Player() {}

//If > 0 after payment return true and do transaction, else return false
bool Player::PayCoin(int amt) {
	bool enoughCoins = false;
	if (coins - amt > 0) {
		coins -= amt;
		enoughCoins = true;
		cout << "Great, you do have enough coins. You currently have " << coins << " coins" << endl;
	}
	else {
		cout << "Sorry, you do not have enough coins. You currently have " << coins << " coins" << endl;
		enoughCoins =  false;
	}
	return enoughCoins;
}
//Loops through all armies and if not placed -> Assigns it a territory
bool Player::PlaceNewArmies(Territory* dest) {
	bool placed = false;
	for (int i = 0; i < cubes.size(); i++) {
		if (!cubes[i]->isPlaced) {
			cubes[i]->location = dest;
			cubes[i]->isPlaced = true;
			placed = true;
			cout << "Successfully put an Army at territoryID: " << dest->territoryID << endl;
			break;
		}
		else
			cout << "You do not have any more armies to place." << endl;
	}
	return placed;
}
//Loops through all armies in a territory -> Assigns it a new territory (calculation for movement imissing)
bool Player::MoveArmies(Territory* src, Territory* dest) {
	bool placed = false;
	for (int i = 0; i < getCubes().size(); i++) {
		if (cubes[i]->location == nullptr)
			continue;
		if (cubes[i]->location->territoryID == src->territoryID) {
			cubes[i]->location = dest;
			placed = true;
			cout << "Successfully destroyed Army at ID " << dest->territoryID << " by army at ID " << src->territoryID << endl;
			//Todo: Need to remove amount of moves based on territoryID
			break;
		}
	}
	return placed;
}
//Loops through all armies in a territory -> Assigns it a new territory (calculation for movement imissing)
bool Player::MoveOverLand(Territory* src, Territory* dest) {
	bool placed = false;
	for (int i = 0; i < getCubes().size(); i++) {
		if (cubes[i]->location == nullptr)
			break;
		if (cubes[i]->location->territoryID == src->territoryID) {
			cubes[i]->location = dest;
			placed = true;
			cout << "Successfully moved Army at ID " << src->territoryID << "to ID " << dest->territoryID << endl;
			//Todo: Need to remove amount of moves based on territoryID
			break;
		}
	}
	return placed;
}
//Returns true if player has a city to build && has an army at the destination
bool Player::BuildCity(Territory* dest) {
	bool cityBuilt = false;
	bool hasArmy = false;
	Disk *city = nullptr;
	//Check if player has a city to build
	for (int i = 0; i < 3; i++) {
		if (!disks[i]->isBuilt) {
			city = disks[i];
			cout << lastName << " has a city to build" << endl;
			break;
		}
		else
			cout << lastName << " does not have a city to build" << endl;
	}
	cout << endl;
	//Check if player has army at location
	for (int j = 0; j < cubes.size(); j++) {
		if (cubes[j]->location != nullptr && cubes[j]->location->territoryID == dest->territoryID) {
			hasArmy = true;
			cout << lastName << " has an army at territory ID: " << dest->territoryID << endl;
			break;
		}
	}
	if (!hasArmy)
		cout << lastName << " does not have an army at territory ID: " << dest->territoryID << endl;
	cout << endl;
	//Check if above conditions are met
	if (hasArmy && city != nullptr) {
		city->location = dest;
		city->isBuilt = true;
		cityBuilt = true;
		cout << lastName << " built a city at territory ID: " << dest->territoryID << endl;
	}
	else 
		cout << lastName << " did not build a city at territory ID: " << dest->territoryID << endl;
	return cityBuilt;
}

//Checks if friendly & ennemy in same location -> Returns if it was destroyed
bool Player::DestroyArmy(Cube* friendly, Cube* ennemy) {
	bool enemyDestoyed = false;
	if (friendly->location->territoryID == ennemy->location->territoryID) {
		ennemy->isPlaced = false;
		ennemy->location = nullptr;
		enemyDestoyed = true;
		cout << "Ennemy has been destroyed" << endl;
	}
	else
		cout << "Ennemy survived!!" << endl;
	return enemyDestoyed;
}

void Player::InitializePlayer() {
	for (int i = 0; i < 18; i++)
		this->cubes.push_back(new Cube());
	for (int j = 0; j < 3; j++)
		this->disks.push_back(new Disk());
	for (int v = 0; v < 3; v++)
		this->hand.push_back(new Card());
}

