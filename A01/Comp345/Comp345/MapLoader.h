#pragma once
#include "Map.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Map;

class MapLoader
{
public:
	MapLoader(string);		// Constructor passing file name
	MapLoader();			// Default constructor
	~MapLoader();			// Destructor
	string userFileName;	// To hold user's file name
	string line;			// To hold input stream line
	ifstream myFile;		// Input stream
	int* regions;			// Dynamic array of regions
	int regionsSize;		// To dynamically change region length
	int i;					// Array index for loops
	int temp;				// Temporary variable to store parsed values from string to int
	int origin;				// Temporary variable to store origin index for variable allocation purposes
private:
	int players;			// To store number of players
	int boards;				// To store number of boards
	int continents;			// To store number of continents
	friend std::ostream& operator<<(std::ostream&, const MapLoader&);
};

int mapLoaderTest();
