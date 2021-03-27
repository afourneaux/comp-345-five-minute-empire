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
const int COST_ONE_ACTIONVALUE = 1;
const int COST_ZERO_ACTIONVALUE = 0;
const int COST_THREE_ACTIONVALUE = 3;

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
	void PayCoin(int amt);
	int PlaceNewArmies();	//Loops through all armies and if not placed -> Assigns it a territory
	int MoveArmies(int numOfMoves);		//Loops through all armies in a territory -> Assigns it a new territory 
	bool PlaceNewArmiesDirectly(int territoryIndex);
	bool MoveOverLand();	//Loops through all armies in a territory -> Assigns it a new territory (calculation for movement imissing)
	int BuildCity();		// if (player has a city to build and has an army at the destination) -> Build city and return true.
	int DestroyArmy();
	int AndOrAction();
	void DoAction(Card* card);
	Cube* GetRandomArmy();
	Cube* GetArmyAtLocation(int id);
	Disk* GetCityAtLocation(int id);
	bool HasArmyAtLocation(int id);
	bool HasCityAtLocation(int id);
	bool HasArmiesOnBoard();
	Territory* GetTerritory(int id);
	Cube* HasArmiesToPlace();
	Disk* HasCitiesToPlace();
	void PrintPlayerStatus();
	void AddCity(Territory* terr);
	void AddArmy(Territory* terr, Cube* cube);
	void RemoveArmy(Territory* terr);
	bool Find(Territory* terr);
	bool HasSkipped(int input);
	void InitializePlayer();
	int ComputeScore();
	void PrintPlacedCities();
	void PrintPlacedArmies();
	void AddCardToHand(Card* card);

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
	int GetPosition() { return position; };
	void setCoins(int amt) { coins = amt; };
	void setPosition(int pos) { position = pos; };

	bool neutralPlayer = false;
private:
	string lastName;
	vector<Territory*> territories;
	vector<Cube*> cubes;
	vector<Disk*> disks;
	vector <Card*> hand;
	BiddingFacility* bf;
	int coins = STARTING_COINS;
	int armiesLeft = STARTING_ARMIES;
	int position; // the position of the player at the table
	int bonusMoves = 0;
	int bonusArmies = 0;
	int bonusFlying = 0;
	bool bonusImmune = false;
};
int testPlayer();

