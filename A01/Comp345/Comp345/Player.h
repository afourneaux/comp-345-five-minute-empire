#pragma once
#include <iostream>
#include <vector>
#include "Map.h"
#include "Cards.h"
#include "BiddingFacility.h"
#include <iostream>
using namespace std;

const int STARTING_COINS = 14;
const int STARTING_ARMIES = 18;

class Map;
struct Card;
class BiddingFacility;

struct Cube {
	Territory* location;
	bool isPlaced;
};
struct Disk {
	Territory* location;
	bool isBuilt = false;
};
struct Player {
public:
	Player();
	~Player();
	Player(const Player* player);
	//Player& operator= (const Player& player);
	friend ostream& operator<<(ostream& out, const Player &player);
	bool PayCoin(int amt);
	bool PlaceNewArmies(Territory* dest);
	bool MoveArmies(Territory* src, Territory* dest);
	bool MoveOverLand(Territory* src, Territory* dest);
	bool BuildCity(Territory* dest);
	bool DestroyArmy(Territory* friendly, Territory* ennemie, Player* ennemy);
	void InitializePlayer();
	//Accessors
	string getLastName() const { return lastName; };
	void setLastName(string last) { lastName = last; };
	vector<Territory*> getTerritories() const { return territories; };
	vector<Cube*> getCubes() const { return cubes; };
	vector<Disk*> getDisks() const { return disks; };
	vector <Card*> getHand() const { return hand; };
	BiddingFacility* getBf() const { return bf; };
	int getCoins() const { return coins; };
	int getArmiesLeft() const { return armiesLeft; };
	void setCoins(int amt) { coins = amt; };

private:
	string lastName;
	vector<Territory*> territories;
	vector<Cube*> cubes;
	vector<Disk*> disks;
	vector <Card*> hand;
	BiddingFacility* bf;
	int coins = STARTING_COINS;
	int armiesLeft = STARTING_ARMIES;
};
int testPlayer();

