#include "Map.h"
#include <iostream>

using namespace std;

//Initializes all vertices/nodes (ie territories) 
//territories array parameter: array indexes correspond to territory indexes, the values at each index correspond to the continent ID (territories[0]==1 -> territory 0 belongs to continent 1)
//Continent IDs are indexed from 0
Map::Map(int* territories, int territory_count, int player_count, int continent_count) {
	this->territory_count = territory_count;
	this->continent_count = continent_count;
	this->player_count = player_count;
	this->starting_territory_index = -1;

	//Initialize continent Linked Lists
	this->continents = new TerritoryList[continent_count];
	for (int i = 0; i < continent_count; i++) {
		this->continents[i].head = nullptr;
		this->continents[i].length = 0;
	}

	//Initialize territories array
	this->territories = new Territory[territory_count];
	for (int i = 0; i < territory_count; i++) {
		this->territories[i].head = nullptr;
		this->territories[i].continentID = territories[i];
		this->territories[i].territoryID = i;
		this->territories[i].army_count = new int[player_count];
		this->territories[i].city_count = new int[player_count];
		//Append territory to its corresponding continent list
		this->continents[territories[i]].head = new TerritoryListNode{ &this->territories[i], continents[territories[i]].head };
		this->continents[territories[i]].length++;
		//initialize player-specific values for each territory
		for (int j = 0; j < player_count; j++) {
			this->territories[i].army_count[j] = 0;
			this->territories[i].city_count[j] = 0;
		}
	}
}


Map::Map(Map* map) {
	this->territory_count = map->territory_count;
	this->continent_count = map->continent_count;
	this->player_count = map->player_count;
	this->starting_territory_index = map->starting_territory_index;

	//Initialize continent Linked Lists
	this->continents = new TerritoryList[continent_count];
	for (int i = 0; i < continent_count; i++) {
		this->continents[i].head = nullptr;
		this->continents[i].length = 0;
	}

	//Initialize territories array and copy
	this->territories = new Territory[territory_count];
	for (int i = 0; i < territory_count; i++) {
		this->territories[i].continentID = map->territories[i].continentID;
		this->territories[i].territoryID = i;
		this->territories[i].army_count = new int[map->player_count];
		this->territories[i].city_count = new int[map->player_count];
		for (int j = 0; j < player_count; j++) {
			this->territories[i].army_count[j] = map->territories[i].army_count[j];
			this->territories[i].city_count[j] = map->territories[i].city_count[j];
		}

		Edge* temp_edge = map->territories[i].head;
		if (temp_edge != nullptr) {
			Edge* prev = this->territories[i].head = new Edge{ &territories[temp_edge->destination_territory->territoryID],temp_edge->movement_cost, nullptr };
			temp_edge = temp_edge->next;

			while (temp_edge != nullptr) {
				prev->next = new Edge{ &territories[temp_edge->destination_territory->territoryID], temp_edge->movement_cost };
				temp_edge = temp_edge->next;
				prev = prev->next;
			}
			prev->next = nullptr;
		}
		//Append territory to its corresponding continent list
		this->continents[map->territories[i].continentID].head = new TerritoryListNode{ &this->territories[i], continents[map->territories[i].continentID].head };
		this->continents[map->territories[i].continentID].length++;
	}
}


Map::~Map() {
	//Iterate through territories and delete corresponding edges
	for (int i = 0; i < territory_count; i++) {
		Edge* current = territories[i].head;
		while (current != nullptr) {
			Edge* temp = current->next;
			delete current;
			current = temp;
		}
		delete[] territories[i].army_count;
		delete[] territories[i].city_count;
	}
	delete[] territories;
	territories = nullptr;

	//Iterate through continents and delete corresponding TerritoryListNodes
	for (int i = 0; i < continent_count; i++) {
		TerritoryList* current = &continents[i];
		TerritoryListNode* terr = current->head;
		while (terr != nullptr) {
			TerritoryListNode* temp = terr->next;
			delete terr;
			terr = temp;
		}
	}
	delete[] continents;
	continents = nullptr;
}


void Map::AddEdge(int origin, int destination) {
	//Check for valid indexes
	if (origin < 0 || origin >= territory_count) {
		cout << "WARNING: Error on adding edge (" << origin << "," << destination << "): origin territory index " << origin << " out of range. Edge not added.\n";
		return;
	}
	else if (destination < 0 || destination >= territory_count) {
		cout << "WARNING: Error on adding edge(" << origin << ", " << destination << ") : destination territory index " << destination << " out of range. Edge not added.\n";
		return;
	}
	//Check if self-loop
	else if (origin == destination) {
		cout << "WARNING: Error on adding edge(" << origin << ", " << destination << ") : self-looping is forbidden. Edge not added.\n";
		return;
	}
	//Check if edge is already defined, if yes then do not add the edge
	Edge* temp = territories[origin].head;
	while (temp != nullptr) {
		if (temp->destination_territory->territoryID == destination) {
			cout << "Skipped creation of edge (" << origin << "," << destination << "), edge already exists." << endl;
			return;
		}
		temp = temp->next;
	}
	//Compute edge cost (ie movement cost)
	int edgeCost{ 1 };
	if (territories[origin].continentID != territories[destination].continentID) edgeCost = 3;
	//Add edge (in both directions)
	territories[origin].head = new Edge{ GetTerritory(destination), edgeCost, territories[origin].head };
	territories[destination].head = new Edge{ GetTerritory(origin), edgeCost, territories[destination].head };
}


void Map::PrintMap() {
	for (int i = 0; i < territory_count; i++) {
		cout << "Territory index " << i << ", ContinentID " << territories[i].continentID << ". Connections to: ";
		Edge* current = territories[i].head;
		while (current != nullptr) {
			cout << current->destination_territory->territoryID << " ";
			current = current->next;
		}
		cout << endl;
		for (int j = 0; j < player_count; j++) {
			cout << "\tPlayer " << j << ": \tarmy count: " << territories[i].army_count[j] << "\tcity count: " << territories[i].city_count[j] << endl;
		}
	}
}


void Map::PrintMapMemAddresses() {
	for (int i = 0; i < territory_count; i++) {
		cout << "DEBUG: PRINTING MEMORY ADDRESSES" << endl;
		cout << "Territory address " << &territories[i] << ", ContinentID " << &territories[i].continentID << ". Connections to: ";
		Edge* current = territories[i].head;
		while (current != nullptr) {
			cout << &current->destination_territory->territoryID << " ";
			current = current->next;
		}
		cout << endl;
		for (int j = 0; j < player_count; j++) {
			cout << "\tPlayer " << j << ": \tarmy count: " << &territories[i].army_count[j] << "\tcity count: " << &territories[i].city_count[j] << endl;
		}
	}
}


bool Map::Validate() {
	//Check if territory count matches the visited node count from a BFS
	if (territory_count != CountContiguousNodes()) {
		cout << "Invalid map: not all territories are connected." << endl;
		return false;
	}
	//Check each continent: count contiguous nodes via BFS, check against continent's territory count
	for (int i = 0; i < continent_count; i++) {
		TerritoryList* continent = &continents[i];
		if (continent->length != CountContiguousNodesInContinent(continent)) {
			cout << "Invalid map: continent " << i << " has non-contiguous territories." << endl;
			return false;
		}
	}
	//Check all outgoing edges for a corresponding incoming edge (shouldn't occur unless an edge is manually removed)
	for (int i = 0; i < territory_count; i++) {
		Edge* outEdge = territories[i].head;
		while (outEdge != nullptr) {
			bool found_incoming = false;
			Edge* inEdge = outEdge->destination_territory->head;
			while (inEdge != nullptr) {
				if (inEdge->destination_territory->territoryID == territories[i].territoryID) {
					found_incoming = true;
					break;
				}
				inEdge = inEdge->next;
			}
			if (!found_incoming) {
				cout << "Invalid map: Territory ID " << i << " has an outgoing edge to " << outEdge->destination_territory->territoryID << " with no corresponding incoming edge." << endl;
				return false;
			}
			outEdge = outEdge->next;
		}
	}
	return true;
}


int Map::CountContiguousNodes() {
	bool* seen = new bool[territory_count];
	for (int i = 0; i < territory_count; i++) seen[i] = false;
	int seenCount{ 0 };
	TerritoryList visitQueue;
	visitQueue.Push(&territories[0]);
	seen[0] = true;
	while (visitQueue.length > 0) {

		seenCount++;
		TerritoryListNode* current = visitQueue.Pop();
		// cout << "DEBUG countContinuousNodes(): Visiting " << current->territory->territoryID << endl;
		Edge* outEdge = current->territory->head;
		while (outEdge != nullptr) {
			if (!seen[outEdge->destination_territory->territoryID]) {
				visitQueue.Push(outEdge->destination_territory);
				seen[outEdge->destination_territory->territoryID]=true;
			}
			outEdge = outEdge->next;
		}
		delete current;
	}
	delete[] seen;
	return seenCount;
}


int Map::CountContiguousNodesInContinent(TerritoryList *continent) {
	if (continent->head == nullptr) return 0;
	bool* seen = new bool[territory_count];
	for (int i = 0; i < territory_count; i++) seen[i] = false;
	int seenCount{ 0 };
	TerritoryList *visitQueue = new TerritoryList();
	visitQueue->Push(continent->head->territory);
	seen[continent->head->territory->territoryID] = true;
	while (visitQueue->length > 0) {
		seenCount++;
		TerritoryListNode* current = visitQueue->Pop();
		// cout << "DEBUG countContinuousNodesInContinent(): Visiting " << current->territory->territoryID << endl;
		Edge* outEdge = current->territory->head;
		while (outEdge != nullptr) {
			if (!seen[outEdge->destination_territory->territoryID] and outEdge->destination_territory->continentID == current->territory->continentID) {
				visitQueue->Push(outEdge->destination_territory);
				seen[outEdge->destination_territory->territoryID] = true;
			}
			outEdge = outEdge->next;
		}
		delete current;
	}
	delete visitQueue;
	delete[] seen;
	return seenCount;
}


int Map::CountWaterConnections(int territory_index)
{
	int count = 0;
	Edge* temp = territories[territory_index].head;
	while (temp != nullptr) {
		if (temp->destination_territory->continentID != territories[territory_index].continentID)
			count++;
		temp = temp->next;
	}
	return count;
}


Territory* Map::GetTerritory(int territory_index) {
	if (territory_index < 0 || territory_index >= territory_count) {
		cout << "ERROR: Failure to fetch territory at index " << territory_index << ", index is out of range." << endl;
		return nullptr;
	}
	return &territories[territory_index];
}


Territory* Map::SetStartingTerritory(int territory_index) {
	int water_connections = CountWaterConnections(territory_index);
	//Reject if territory does not have a water connection to another continent
	if (water_connections == 0) {
		cout << "ERROR: invalid starting territory " << territory_index << ", the starting territory must have at least one connection to another continent";
		return nullptr;
	}
	//If there is one connection, accept if an adjacent territory (on same continent) has a water connection, otherwise reject
	else if (water_connections == 1) {
		int count = 0;
		Edge* temp = territories[territory_index].head;
		while (temp != nullptr) {
			if (temp->destination_territory->continentID == territories[territory_index].continentID and CountWaterConnections(temp->destination_territory->territoryID) > 0) {
				starting_territory_index = territory_index;
				return &territories[territory_index];
			}
			temp = temp->next;
		}
		return nullptr;
	}
	// Accept if territory has 2 or more water connections
	else {
		starting_territory_index = territory_index;
		return &territories[territory_index];
	}
}

std::ostream& operator<< (std::ostream& out, const Map& map) {
	for (int i = 0; i < map.territory_count; i++) {		
		out << "Territory index " << i << ", ContinentID " << map.territories[i].continentID << ". Connections to: ";
		Edge* current = map.territories[i].head;
		while (current != nullptr) {
			out << current->destination_territory->territoryID << " ";
			current = current->next;
		}
		out << endl;
		for (int j = 0; j < map.player_count; j++) {
			out << "\tPlayer " << j << ": \tarmy count: " << map.territories[i].army_count[j] << "\tcity count: " << map.territories[i].city_count[j] << endl;
		}
	}
	return out;
}


TerritoryList::TerritoryList() {
	head = nullptr;
	length = 0;
}


void TerritoryList::Push(Territory* territory) {
	this->head = new TerritoryListNode{ territory, this->head };
	this->length++;
}


TerritoryListNode* TerritoryList::Pop() {
	if (this->head == nullptr) return nullptr;
	this->length--;
	TerritoryListNode* temp = this->head;
	head = temp->next;
	return temp;
}

