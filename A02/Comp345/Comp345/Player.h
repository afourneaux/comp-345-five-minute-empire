#pragma once
#include <iostream>
#include <vector>
#include "Cards.h"
#include "BiddingFacility.h"
#include "Map.h"
#include <iostream>
using namespace std;

const int STARTING_COINS = 14;
const int STARTING_ARMIES = 18;
static vector<Player*> round_table;

class Map;
struct Card;
class BiddingFacility;
class Game;

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
	Player& operator= (const Player& player);
	friend std::ostream& operator<<(std::ostream& out, const Player &player);
	bool PayCoin(int amt);
	bool PlaceNewArmies();//Loops through all armies and if not placed -> Assigns it a territory
	bool MoveArmies();//Loops through all armies in a territory -> Assigns it a new territory (calculation for movement imissing)
	bool MoveOverLand(); //Loops through all armies in a territory -> Assigns it a new territory (calculation for movement imissing)
	bool BuildCity(); // if (player has a city to build and has an army at the destination) -> Build city and return true.
	bool DestroyArmy();
	bool DoAction(Card* card);
	Cube* HasArmyAtLocation(int id);
	Disk* HasCityAtLocation(int id);
	Territory* GetTerritory(int id);
	bool HasArmiesToPlace();
	void PlayerStatus();
	void InitializePlayer();

	//Accessors
	string GetLastName() const { return lastName; };
	void SetLastName(string last) { lastName = last; };
	vector<Territory*> GetTerritories() const { return territories; };
	vector<Cube*> getCubes() const { return cubes; };
	vector<Disk*> getDisks() const { return disks; };
	vector <Card*> getHand() const { return hand; };
	BiddingFacility* GetBf() const { return bf; };
	int getCoins() const { return coins; };
	int getArmiesLeft() const { return armiesLeft; };
	void SetCoins(int amt) { coins = amt; };
	int GetPos() { return pos; };
	void setCoins(int amt) { coins = amt; };
	void setPosition(int pos) { position = pos; };

private:
	string lastName;
	vector<Territory*> territories;
	vector<Cube*> cubes;
	vector<Disk*> disks;
	vector <Card*> hand;
	BiddingFacility* bf;
	int coins = STARTING_COINS;
	int armiesLeft = STARTING_ARMIES;
	int STARTING_REGION_ID = 0;
	int pos;
	int position; // the position of the player at the table
};
int testPlayer();

