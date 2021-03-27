#include "Map.h"
#include "MapLoader.h"
#include "Game.h"
#include <iostream>
#include <algorithm>

using namespace std;

extern Game* MasterGame;

Map::Map() {

}

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
		this->territories[i].army_count.resize(player_count);
		this->territories[i].city_count.resize(player_count);
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
		this->territories[i].army_count.resize(map->player_count);
		this->territories[i].city_count.resize(map->player_count);
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
		//delete territories[i].army_count;
		//delete territories[i].city_count;
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
	int edgeCost{ LAND_MOVEMENT_COST };
	if (territories[origin].continentID != territories[destination].continentID) edgeCost = WATER_MOVEMENT_COST;
	//Add edge (in both directions)
	territories[origin].head = new Edge{ GetTerritory(destination), edgeCost, territories[origin].head };
	territories[destination].head = new Edge{ GetTerritory(origin), edgeCost, territories[destination].head };
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
		Edge* outEdge = current->territory->head;
		while (outEdge != nullptr) {
			if (!seen[outEdge->destination_territory->territoryID]) {
				visitQueue.Push(outEdge->destination_territory);
				seen[outEdge->destination_territory->territoryID] = true;
			}
			outEdge = outEdge->next;
		}
		delete current;
	}
	delete[] seen;
	return seenCount;
}


int Map::CountContiguousNodesInContinent(TerritoryList* continent) {
	if (continent->head == nullptr) return 0;
	bool* seen = new bool[territory_count];
	for (int i = 0; i < territory_count; i++) seen[i] = false;
	int seenCount{ 0 };
	TerritoryList* visitQueue = new TerritoryList();
	visitQueue->Push(continent->head->territory);
	seen[continent->head->territory->territoryID] = true;
	while (visitQueue->length > 0) {
		seenCount++;
		TerritoryListNode* current = visitQueue->Pop();
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


int Map::CountWaterConnections(int territory_index) {
	int count = 0;
	Edge* temp = territories[territory_index].head;
	while (temp != nullptr) {
		if (temp->destination_territory->continentID != territories[territory_index].continentID)
			count++;
		temp = temp->next;
	}
	return count;
}

// Checks if two territories are adjacent
// Returns -1 if they are not adjacent, otherwise returns the movement cost (1 or 3)
int Map::CheckAdjacency(int origin, int destination) {
	Edge* temp = territories[origin].head;
	while (temp != nullptr) {
		if (temp->destination_territory->territoryID == destination) {
			return temp->movement_cost;
		}
		temp = temp->next;
	}
	return -1;
}

vector<int> Map::GetLegalArmyPlacements(int playerIndex) {
	vector<int> potentialTerritories;
	for (int i = 0; i < territory_count; i++) {
		if (i == starting_territory_index) potentialTerritories.push_back(i);
		else if (territories[i].city_count[playerIndex]>0) potentialTerritories.push_back(i);
	}
	return potentialTerritories;
}


Territory* Map::GetTerritory(int territory_index) {
	if (territory_index < 0 || territory_index >= territory_count) {
		cout << "ERROR: Failure to fetch territory at index " << territory_index << ", index is out of range." << endl;
		return nullptr;
	}
	return &territories[territory_index];
}

vector<int> Map::GetPotentialStartingTerritories() {
	vector<int> potential_starters;
	for (int territory_index = 0; territory_index < territory_count; territory_index++) {
		int water_connections = CountWaterConnections(territory_index);
		//Reject if territory does not have a water connection to another continent
		if (water_connections == 0) {
			continue;
		}
		//If there is one connection, accept if an adjacent territory (on same continent) has a water connection, otherwise reject
		else if (water_connections == 1) {
			int count = 0;
			Edge* temp = territories[territory_index].head;
			while (temp != nullptr) {
				if (temp->destination_territory->continentID == territories[territory_index].continentID and CountWaterConnections(temp->destination_territory->territoryID) > 0) {
					potential_starters.push_back(territory_index);
					break;
				}
				temp = temp->next;
			}
			continue;
		}
		// Accept if territory has 2 or more water connections
		else {
			potential_starters.push_back(territory_index);
		}
	}

	return potential_starters;
}

Territory* Map::SetStartingTerritory(int territory_index) {
	int water_connections = CountWaterConnections(territory_index);
	//Reject if territory does not have a water connection to another continent
	if (water_connections == 0) {
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




Map& Map::operator= (const Map& map) {
	//Check for self-assignment
	if (this == &map) {
		return *this;
	}

	//Deallocate currently used memory:
	//Iterate through territories and delete corresponding edges
	for (int i = 0; i < territory_count; i++) {
		Edge* current = territories[i].head;
		while (current != nullptr) {
			Edge* temp = current->next;
			delete current;
			current = temp;
		}
		//delete[] territories[i].army_count;
		//delete[] territories[i].city_count;
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

	//reallocate new values:
	this->territory_count = map.territory_count;
	this->continent_count = map.continent_count;
	this->player_count = map.player_count;
	this->starting_territory_index = map.starting_territory_index;

	//Initialize continent Linked Lists
	this->continents = new TerritoryList[continent_count];
	for (int i = 0; i < continent_count; i++) {
		this->continents[i].head = nullptr;
		this->continents[i].length = 0;
	}

	//Initialize territories array and copy
	this->territories = new Territory[territory_count];
	for (int i = 0; i < territory_count; i++) {
		this->territories[i].continentID = map.territories[i].continentID;
		this->territories[i].territoryID = i;
		this->territories[i].army_count.resize(map.player_count);
		this->territories[i].city_count.resize(map.player_count);
		for (int j = 0; j < player_count; j++) {
			this->territories[i].army_count[j] = map.territories[i].army_count[j];
			this->territories[i].city_count[j] = map.territories[i].city_count[j];
		}

		Edge* temp_edge = map.territories[i].head;
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
		this->continents[map.territories[i].continentID].head = new TerritoryListNode{ &this->territories[i], continents[map.territories[i].continentID].head };
		this->continents[map.territories[i].continentID].length++;
	}

	return *this;
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
			out << "\tPlayer " << MasterGame->players[j]->GetLastName() << ": \tarmy count: " << map.territories[i].army_count[j] << "\tcity count: " << map.territories[i].city_count[j] << endl;
		}
		out << "Controlling player: " << map.territories[i].controlling_player_name << endl;
	}
	return out;
}

int Map::ComputeMapScore(int playerIndex) {
	int score{0};
	//Loop through territories and increment each player's score for each territory they control
	cout << "Territories controlled by player " << MasterGame->players[playerIndex]->GetLastName() << ": ";
	for (int i = 0; i < territory_count; i++) {
		if (territories[i].controlling_player == playerIndex) {
			score++;
			cout << i << " ";
		}
	}
	cout << endl;

	cout << "Player " << MasterGame->players[playerIndex]->GetLastName() << " score for controlled territories: " << score << endl;

	//Loop through each continent
	for (int i = 0; i < continent_count; i++) {
		int* continent_scores = new int[player_count];
		for (int j = 0; j < player_count; j++) continent_scores[j] = 0;
		//count the number of territories each player controls on the continent
		TerritoryListNode* temp = continents[i].head;
		while (temp != nullptr) {
			int controller = temp->territory->controlling_player;
			if (controller == -1) {
				temp = temp->next;
				continue;
			}
			continent_scores[controller]++;
			temp = temp->next;
		}
		// give 1 point to the player who controls the most territories in the continent (no points if tied)
		int winning_player = -1;
		int max_terr_controlled = -1;
		for (int j = 0; j < player_count; j++) {
			if (continent_scores[j] > max_terr_controlled) {
				winning_player = j;
				max_terr_controlled = continent_scores[j];
			}
			else if (continent_scores[j] == max_terr_controlled) {
				winning_player = -1;
			}
		}
		if (winning_player == playerIndex) {
			cout << "Player " << MasterGame->players[playerIndex]->GetLastName() << " controls Continent " << i << ", gets 1 bonus point." << endl;
			score++;
		}
			
		delete[] continent_scores;

	}

	return score;

}

int Map::getNumberControlledTerritories(int playerIndex) {
	int count{ 0 };
	for (int i = 0; i < territory_count; i++) {
		if (territories[i].controlling_player == playerIndex) {
			count++;
		}
	}
	return count;
}

// Calculates the movement cost for the shortest path between origin and destination
int Map::GetMovementCost(int origin, int destination, int bonusFlying) {
	bool* visited = new bool[territory_count];
	int* distance = new int[territory_count];
	int current_node = origin;
	for (int i = 0; i < territory_count; i++) {
		visited[i] = false;
		if (i == origin) distance[i] = 0;
		else distance[i] = INT32_MAX;
	}
	// Loop until a path is found
	while (true) {
		//iterate over ajcency list of current node and update their distances if they are shorter than the current minimum
		Edge* temp = territories[current_node].head;
		while (temp != nullptr) {
			int candidate_distance = distance[current_node] + max(temp->movement_cost - bonusFlying, 1);
			if (!visited[temp->destination_territory->territoryID] && candidate_distance < distance[temp->destination_territory->territoryID]) {
				distance[temp->destination_territory->territoryID] = candidate_distance;
			}
			temp = temp->next;
		}
		// Mark current node as visited
		visited[current_node] = true;
		if (current_node == destination) {
			// if the current node is the destination, shortest path length is stored as distance
			int shortest = distance[current_node];
			delete[] visited;
			delete[] distance;
			return shortest;
		}
		//select the unvisited node with smallest distance and loop
		int shortest_unvisited = INT32_MAX;
		for (int i = 0; i < territory_count; i++) {
			if (visited[i]) continue;
			if (distance[i] <= shortest_unvisited) {
				shortest_unvisited = distance[i];
				current_node = i;
			}
		}
		if (visited[current_node]) break;
	}

	cout << "ERROR when calculating shortest path between " << origin << " and " << destination << ". No valid path found. Check that the map is valid." << endl;
	delete[] visited;
	delete[] distance;
	return -1;
}

void Territory::addArmy(int player_index) {
	army_count[player_index]++;
	UpdateControl();
}

void Territory::addCity(int player_index) {
	city_count[player_index]++;
	UpdateControl();
}

void Territory::removeArmy(int player_index) {
	army_count[player_index]--;
	UpdateControl();
}

// Checks if two territories are adjacent
// Returns -1 if they are not adjacent, otherwise returns the movement cost (1 or 3)
int Territory::CheckAdjacency(Territory* destination) {
	Edge* temp = this->head;
	while (temp != nullptr) {
		if (temp->destination_territory->territoryID == destination->territoryID) {
			return temp->movement_cost;
		}
		temp = temp->next;
	}
	return -1;
}

std::vector<int> Territory::GetAdjacent() {
	vector<int> adjacentTerritories;
	Edge* temp = this->head;
	while (temp != nullptr) {
		adjacentTerritories.push_back(temp->destination_territory->territoryID);
		temp = temp->next;
	}
	return adjacentTerritories;
}

void Territory::UpdateControl() {
	int current_max = -1;
	if (controlling_player != -1) {
		current_max = army_count[controlling_player] + city_count[controlling_player];
	}
	for (int i = 0; i < army_count.size(); i++) {
		if (i == controlling_player) continue;
		int player_control_score = army_count[i] + city_count[i];
		if (current_max == player_control_score){
			controlling_player = -1;
			controlling_player_name = "None";
		}
		else if (current_max < player_control_score) {
			controlling_player = i;
			controlling_player_name = MasterGame->players[i]->GetLastName();
			current_max = player_control_score;
		}
	}
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
