#pragma once
#include <iostream>		// used for cin & cout
#include <fstream>		// used for file i/o
#include <string>
#include "MapLoader.h"

using namespace std;

MapLoader::MapLoader() {
	players = 0;
	boards = 0;
	continents = 0;
	regionsSize = 0;
	line = "";
	userFileName = "";
	i = 0;
	temp = 0;
	validity = 0;
}

MapLoader::MapLoader(string filename) {
	players = 0;
	boards = 0;
	regionsSize = 0;
	line = "";
	userFileName = filename;
	i = 0;
	origin = 0;
	validity = 0;
}

void MapLoader::readFile()
{
	myFile.open(".\\Maps\\" + userFileName);// Open stream file

	//--------------------------------------//
	//----------Read # of players-----------//
	//--------------------------------------//
	myFile.ignore(100, '\n');				// Ignore label string
	myFile >> line;							// Store number of players in line variable
	players = stoi(line);					// Parse line to int and store value in players

	//--------------------------------------//
	//--------Determine # of boards---------//
	//--------------------------------------//
	if (players == 3) {						// Check for valid number of users
		boards = 3;							// Assign 3 continents for 2-3 users
	} else if (players == 4) {
		boards = 4;							// Assign 4 continents for 4 users
	}

	//--------------------------------------//
	//----------Read # of regions-----------//
	//--------------------------------------//
	myFile.ignore(100, '\n');				// Ignore label string
	myFile.ignore(100, '\n');				// Ignore label string
	myFile >> line;							// Store number of regions
	regionsSize = stoi(line);				// Parse line to int and store value in regionsSize
	this->regions = new int[regionsSize];	// Assign length of regions array

	//--------------------------------------//
	//--Read each region's continent label--//
	//--------------------------------------//
	myFile.ignore(100, '\n');				// Ignore label
	myFile.ignore(100, '\n');				// Ignore label
	for (i = 0; i < regionsSize; i++) {		// Loop through the regions array and label them with a continent
		myFile >> line;						// Read region entry, but skip it
		myFile >> line;						// Read continent of the region index read above
		regions[i] = stoi(line);			// Parse to int and store it (not sure how to fix the warnings)
	}

	//--------------------------------------//
	//----Determine number of continents----//
	//--------------------------------------//
	for (i = 0; i < regionsSize; i++) {
		if (continents <= regions[i]) {		// if # of continents < region's continent label
			continents = regions[i] + 1;	// # of continents = continent # + 1 (+1 because it's enumerated by index)
		}
	}
}

Map* MapLoader::buildMap(int* regions, int regionsSize, int players, int continents)
{
	//--------------------------------------//
	//----------Create map object-----------//
	//--------------------------------------//
	Map *userMap = new Map(regions, regionsSize, players, continents); // Use map class to create map
	myFile.ignore(100, '\n');				// Ignore label
	myFile.ignore(100, '\n');				// Ignore label

	for (i = 0; i < regionsSize; i++) {		// Loop through region indexes and add adjacent edges
		myFile >> line;						// Read origin index
		origin = stoi(line);
		while (line != ".") {				// '.' is a delimeter, if you match it then stop connecting regions within that board
			myFile >> line;					// Store adjacent territory
			if (line == ".") {				// Conditional to prevent a MASSIVE ERROR!
				break;						// just so we don't parse a non-numerical string
			}
			temp = stoi(line);				// Parse adjacent territory to int
			userMap->AddEdge(origin, temp);	// Add edge to and from origin
		}
	}

	//--------------------------------------//
	//------Connect maps to each other------//
	//--------------------------------------//
	myFile.ignore(100, '\n');				// Ignore label
	myFile.ignore(100, '\n');				// Ignore label

	temp = 0;								// Reset values for destination index
	origin = 0;								// Reset values for origin index

	myFile >> line;							// Read first value index
	if (line != ".") {						// If line == '.' there are no regions in board
		origin = stoi(line);				// Store index in origin
	}
	myFile.ignore(100, '\n');				// Ignore the rest of the index for this line

	myFile >> line;
	if (line != ".") {						
		temp = stoi(line);
	}
	myFile.ignore(100, '\n');

	if (line != ".") {
		userMap->AddEdge(origin, temp);		// Add edge to and from origin
	}

	origin = temp;							// Replace destination with origin
	
	myFile >> line;
	if (line != ".") {
		temp = stoi(line);
	}

	if (line != ".") {
		userMap->AddEdge(origin, temp);		// Add edge to and from origin
	}

	if (boards == 4) {						// Do this process again if we need to connect 4 maps
		myFile.ignore(100, '\n');
		origin = temp;						// Replace destination with origin
		myFile >> line;

		if (line != ".") {
			temp = stoi(line);
		}
		myFile.ignore(100, '\n');

		if (line != ".") {
			userMap->AddEdge(origin, temp);	// Add edge to and from origin
		}
	}

	//--------------------------------------//
	//----------Validate user map-----------//
	//--------------------------------------//
	validity = userMap->Validate();
	cout << "Map validate() result (1 = Valid | 0 = Invalid): " << validity << endl;

	delete[] regions;
	regions = nullptr;

	myFile.close();

	return userMap;
}


std::ostream& operator<<(std::ostream& strm, const MapLoader& file)
{
	return strm << "MapLoader(" << file.userFileName << ")";
}