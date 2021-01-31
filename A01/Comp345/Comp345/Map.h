#pragma once

struct Edge;

struct Territory {
	Edge* head;
	int continentID;
	int territoryID;
	//army_count and city_count are arrays indexed by player index (eg if player 0 has 5 armies in the territory, army_count[0]==5)
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

//TODO: assignment operator, stream insertion
class Map {
public:
	int territory_count;
	int continent_count;
	int player_count;
	Territory* territories;
	TerritoryList* continents;
	Map(int *territories, int territory_count, int player_count, int continent_count);
	Map(Map* map);
	~Map();
	void addEdge(int origin, int destination);
	Territory* getTerritory(int territory_index);
	void printMap();
	void printMapMemAddresses();
	bool validate();
private:
	int countContiguousNodes();
	int countContiguousNodesInContinent(TerritoryList* continent);
};

int testMap();
