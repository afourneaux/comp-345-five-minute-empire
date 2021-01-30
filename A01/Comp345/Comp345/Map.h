#pragma once

struct Edge;

struct Territory {
	Edge* head;
	//Player *controlling_player;
	int continentID;
	int territoryID;
	//army_count and city_count are arrays indexed by player index (eg if player 0 has 5 armies in the territory, army_count[0]==5)
	//TODO: is this something we want to store in the territory object or in the player object?
	int* army_count;
	int* city_count;
};

struct Edge {
	Territory* destination_territory;
	int movement_cost;
	Edge* next;
};

struct TerritoryListNode {
	Territory* territory;
	TerritoryListNode* next;
};

struct TerritoryList {
	TerritoryListNode* head;
	int length;
	TerritoryList();
	void push(Territory* territory);
	TerritoryListNode* pop();
};

//TODO: copy constructor, assignment operator, stream insertion
class Map {
public:
	int territory_count;
	int continent_count;
	Territory* territories;
	TerritoryList* continents;
	Map(int *territories, int territory_count, int player_count, int continent_count);
	~Map();
	void addEdge(int origin, int destination);
	Territory* getTerritory(int territory_index);
	void printMap();
	bool validate();
private:
	int countContiguousNodes();
	int countContiguousNodesInContinent(TerritoryList* continent);
};

int testMap();
