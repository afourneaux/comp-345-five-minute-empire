#pragma once
#include <iostream>
#include <vector>

struct Edge;

struct Territory {
	Edge* head;							// Pointer to head of linked list of edge objects (edge object contains a pointer to an adjacent territory)
	int continentID;					// Index of continent that the territory belongs to - maps to continents[] array in Map class
	int territoryID;					// Index of the territory in the territories[] array of Map class
	std::vector<int> army_count;				// army_count and city_count are arrays indexed by player index (eg if player 0 has 5 armies in the territory, army_count[0]==5)
	std::vector<int> city_count;
	int controlling_player = -1;
	std::string controlling_player_name = "None";
	int max_count = 0;
	void addArmy(int player_index);
	void addCity(int player_index);
	void removeArmy(int player_index);
	void UpdateControl();
	int CheckAdjacency(Territory* destination);	// Checks if the current territory and destination are adjacent. Returns the movement cost if they are connected, otherwise -1
	std::vector<int> GetAdjacent();
};

struct Edge {
	Territory* destination_territory;	// Pointer to territory that is adjacent to the territory the linked list belongs to
	int movement_cost;					// Movement cost associated with moving an army along edge (water=3, land=1)
	Edge* next;							// Next edge in linked list
};

struct TerritoryListNode {				// Node for use in TerritoryList linked list data structure
	Territory* territory;				// Pointer to territory
	TerritoryListNode* next;			// Next Node in linked list
};

struct TerritoryList {					// Territorylist is a generic linked list data structure for tracking territories 
	TerritoryListNode* head;			// Head of list
	int length;							// length of linked list
	int controlling_player = -1;		// The player controlling the most territories on the continent
	TerritoryList();					// Default constructor
	void Push(Territory* territory);	// Adds a territory to front of linked list
	TerritoryListNode* Pop();			// Removes first territory from linked list
};

class Map {
public:
	int territory_count;							// Number of territories in Map
	int continent_count;							// Number of continents in Map
	int player_count;								// Number of players in Map
	int starting_territory_index;					// Index of starting territory for army placement
	Territory* territories;							// Array of Territory objects - each Territory contains a linked list of Edges which are pointers to adjacent territories 
	TerritoryList* continents;						// Array of linked lists mapping territories to continents
	Map();											// Default constructor
	Map(int* territories, int territory_count, int player_count, int continent_count); // Parameterized constructor (territories* is an array mapping territories to their continent)
	Map(Map* map);									// Copy constructor
	~Map();											// Destructor
	void AddEdge(int origin, int destination);		// Adds a bi-directional edge from territories[origin] to territories[destination]
	int CheckAdjacency(int origin, int destination);// Checks if two territories are adjacent. Returns the movement cost if they are connected, otherwise -1
	std::vector<int> GetLegalArmyPlacements(int playerIndex);
	Territory* GetTerritory(int territory_index);	// Returns a pointer to the territory at the specified index
	std::vector<int> GetPotentialStartingTerritories();
	Territory* SetStartingTerritory(int territory_index);	// Sets the starting territory for army placement
	void PrintMapMemAddresses();					// DEBUG: prints a string representation of the map's memory addresses
	bool Validate();								// Validates if the map is a valid game map
	int ComputeMapScore(int playerIndex);
	Map& operator= (const Map& map);				// Assignment operator
	friend std::ostream& operator<< (std::ostream& out, const Map& map); // Stream insertion operator
	int getNumberControlledTerritories(int playerIndex);
private:
	const int LAND_MOVEMENT_COST = 1;
	const int WATER_MOVEMENT_COST = 3;
	int CountContiguousNodes();						// Used in validate() to check that all territories are connected
	int CountContiguousNodesInContinent(TerritoryList* continent);	// Used in validate() to check that all continents are contiguous
	int CountWaterConnections(int territory_index);	// Used in setStartingTerritory() to check if the placement is valid
};

int TestMap();