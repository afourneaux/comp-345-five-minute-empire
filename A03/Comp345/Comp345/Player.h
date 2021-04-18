#pragma once
#include <iostream>
#include <vector>
#include "Cards.h"
#include "BiddingFacility.h"
#include "Map.h"
#include <iostream>
#include "Strategy.h"
using namespace std;

const int STARTING_COINS = 14;
const int STARTING_ARMIES = 18;
const int COST_ONE_ACTIONVALUE = 1;
const int COST_ZERO_ACTIONVALUE = 0;
const int COST_THREE_ACTIONVALUE = 3;
const int TRACKED_CARD_COUNT = 8;
const string TRACKED_CARD_NAMES[TRACKED_CARD_COUNT] = { "Dire", "Forest", "Cursed", "Arcane", "Ancient", "Night", "Mountain", "Noble" };

class Map;
struct Card;
class BiddingFacility;
class Game;
struct Strategy;

struct Cube {
	Territory* location;
	bool isPlaced;
};
struct Disk {
	Territory* location;
	bool isBuilt = false;
};
struct Player: public Subject {
public:
	Player(int pos);
	~Player();
	Player(const Player* player);
	Player& operator= (const Player& player);
	friend std::ostream& operator<<(std::ostream& out, const Player &player);
	void PayCoin(int amt);
	int PlaceNewArmies();	//Loops through all armies and if not placed -> Assigns it a territory
	int MoveArmies(int numOfMoves);		//Loops through all armies in a territory -> Assigns it a new territory 
	bool PlaceNewArmiesDirectly(int territoryIndex);
	bool MoveOverLand();	//Loops through all armies in a territory -> Assigns it a new territory (calculation for movement imissing)
	bool MoveOverSea();	//Loops through all armies in a territory -> Assigns it a new territory (calculation for movement imissing)
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
	void MoveArmy(Territory* src, Territory* dest, Cube* cube);
	bool Find(Territory* terr);
	bool HasSkipped(int input);
	void InitializePlayer(int pos);
	int ComputeScore();
	void PrintPlacedCities();
	void PrintPlacedArmies();
	void AddCardToHand(Card* card);

	//Accessors
	string GetLastName() const { return lastName; };
	void SetLastName(string last) { lastName = last; };
	vector<Territory*> GetTerritories() const { return territories; };
	vector<Cube*> GetCubes() const { return cubes; };
	vector<Disk*> GetDisks() const { return disks; };
	vector <Card*> GetHand() const { return hand; };
	BiddingFacility* GetBf() const { return bf; };
	int GetCoins() const { return coins; };
	int GetArmiesLeft() const { return armiesLeft; };
	void SetCoins(int amt) { coins = amt; };
	int GetPosition() { return position; };
	void SetPosition(int pos) { position = pos; };
	void SetStrategy(Strategy* straty) { strat = straty; };
	Strategy* GetStrategy() { return strat; };
	string GetLastName() { return lastName; };
	int GetBonusMoves() { return bonusMoves; };
	int GetBonusArmies() { return bonusArmies; };
	int GetBonusFlying() { return bonusFlying; };
	bool GetBonusImmune() { return bonusImmune; };
	void SetBonusMoves(int val) { bonusMoves = val; };
	void SetBonusArmies(int val) { bonusArmies = val; };
	void SetBonusFlying(int val) { bonusFlying = val; };
	void SetBonusImmune(bool val) { bonusImmune = val; };
	int getElixirs() { return elixirs; };
	bool getElixirWinner() { return elixirWinner; }
	bool getBonusForFlying() { return bonusForFlying; };
	bool getBonusForCoins() { return bonusForCoins; };
	int getTerritoryScore() { return territoryScore; };
	int getContinentScore() { return continentScore; };
	int getCardScore() { return cardScore; };
	int getTotalScore() { return totalScore; };

	int cardsByTrackedName[TRACKED_CARD_COUNT]{};
	bool bonusForTrackedName[TRACKED_CARD_COUNT]{};
	bool neutralPlayer = false;

	vector<string> actions; // compilation of actions taken by a player
private:
	string lastName;
	vector<Territory*> territories;
	vector<Cube*> cubes;
	vector<Disk*> disks;
	vector <Card*> hand;
	BiddingFacility* bf;
	Strategy* strat;
	int coins = STARTING_COINS;
	int armiesLeft = STARTING_ARMIES;
	int position; // the position of the player at the table
	int elixirs = 0;
	int bonusMoves = 0;
	int bonusArmies = 0;
	int bonusFlying = 0;
	bool bonusForFlying = false;
	bool bonusForCoins = false;
	bool bonusImmune = false;
	int territoryScore = 0;
	int continentScore = 0;
	int cardScore = 0;
	bool elixirWinner = false;
	int totalScore = 0;
};
int testPlayer();

