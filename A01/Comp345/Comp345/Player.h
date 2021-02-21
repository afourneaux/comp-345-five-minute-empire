#pragma once
#include <iostream>
#include <vector>
#include "Map.h"
#include "Card.h"
#include <iostream>
using namespace std;
struct Cube {
	Territory* location;
	bool isPlaced = false;
};
struct Disk {
	Territory* location;
	bool isBuilt = false;
};
struct BidingFacility {
};
struct Player {
public:
	Player();
	~Player();
	bool PayCoin(int amt);
	bool PlaceNewArmies(Territory* dest);
	bool MoveArmies(Territory* src, Territory* dest);
	bool MoveOverLand(Territory* src, Territory* dest);
	bool BuildCity(Territory* dest);
	bool DestroyArmy(Cube* friendly, Cube* ennemie);
	void InitializePlayer();
	//Accessors
	string getLastName() { return lastName; };
	void setLastName(string last) { lastName = last; };
	vector<Territory*> getTerritories() { return territories; };
	vector<Cube*> getCubes() { return cubes; };
	vector<Disk*> getDisks() { return disks; };
	vector <Card*> getHand() { return hand; };
	BidingFacility* getBf() { return bf; };
	int getCoins() { return coins; };
	void setCoins(int amt) { coins = amt; };

private:
	string lastName = "";
	vector<Territory*> territories;
	vector<Cube*> cubes;
	vector<Disk*> disks;
	vector <Card*> hand;
	BidingFacility* bf;
	int coins = 14;
};

