#pragma once
#include "MapLoader.h"
#include <iostream>		// used for cin & cout
#include <fstream>		// used for file i/o

using namespace std;

MapLoader::MapLoader() {
	this->players = 0;
	this->boards = 0;
	this->continents = 0;
	this->regionsSize = 0;
	this->line = "";
	this->userFileName = "";
	this->i = 0;
	this->temp = 0;
	cout << "Where file name, amigo? No me gusta this." << endl;
}

MapLoader::MapLoader(string filename) {
	this->players = 0;
	this->boards = 0;
	this->regionsSize = 0;
	this->line = "";
	this->userFileName = filename;
	this->i = 0;
	this->origin = 0;
	myFile.open(filename);					// Open stream file
	
	// Read # of players
	myFile.ignore(100, '\n');				// Ignore label string
	myFile >> line;							// Store number of players in line variable
	players = stoi(line);					// Parse line to int and store value in players
	cout << "Players: " << players << endl;	// Print players

	// Determine number of boards
	if (players == 2 || players == 3) {		// Check for valid number of users
		boards = 3;							// Assign 3 continents for 2-3 users
	}
	else if (players == 4) {
		boards = 4;							// Assign 4 continents for 4 users
	}
	else {
		throw "Invalid number of players";  // Throw error if numbers of users is not between 2 and 4
	}
	cout << "Boards: " << boards << endl;

	// Read # of regions
	myFile.ignore(100, '\n');				// Ignore label string
	myFile.ignore(100, '\n');				// Ignore label string
	myFile >> line;							// Store number of regions
	regionsSize = stoi(line);				// Parse line to int and store value in regionsSize
	cout << "Regions: " << regionsSize << endl;
	this->regions = new int[regionsSize];	// Assign length of regions array
	
	// Read # continents for every region
	myFile.ignore(100, '\n');				// Ignore label
	cout << "Index region and Index continent: " << endl;

	// Read continent label for every regions
	myFile.ignore(100, '\n');				// Ignore label
	for (i = 0; i < regionsSize; i++) {		// Loop through the regions array and label them with a continent
		myFile >> line;						// Read region entry, but skip it
		myFile >> line;						// Read continent of the region index read above
		regions[i] = stoi(line);			// Parse to int and store it (not sure how to fix the warnings)
		cout << "Region[" << i << "]: " << regions[i] << endl;
	}

	// Determine number of continents
	for (i = 0; i < regionsSize; i++) {
		if (continents < regions[i]) {
			continents = regions[i] + 1;
		}
	}
	cout << "Continents: " << continents << endl;

	// Finally time to make our map!
	Map* userMap = new Map(regions, regionsSize, players, continents); // Use map class to create map
	myFile.ignore(100, '\n');				// Ignore label
	myFile.ignore(100, '\n');				// Ignore label

	for (i = 0; i < regionsSize; i++) {		// Loop through region indexes and add adjacent edges
		myFile >> line;						// Read origin index
		origin = stoi(line);
		while (line != ".") {				// '.' is a delimeter, if you match it then stop connecting regions within that board
			myFile >> line;					// Store adjacent territory
			if (line == ".") {				// Conditional to prevent a MASSIVE ERROR!
				break;						//		just so we don't parse a non-numerical string
			}
			temp = stoi(line);				// Parse adjacent territory to int
			userMap->AddEdge(origin, temp);	// Add edge to and from origin
			cout << "New edge added: [" << origin << "<-->" << temp << "]" << endl;
		}
	}
	
	// To connect maps to each other!
	myFile.ignore(100, '\n');				// Ignore label
	myFile.ignore(100, '\n');				// Ignore label

	temp = 0;								// Reset values for destination index
	origin = 0;								// Rest values for origin index

	myFile >> line;							// Read index
	if (line != ".") {
		origin = stoi(line);				// Store index
	}
	myFile.ignore(100, '\n');				// Ignore the rest of the index for this line

	cout << "Origin: " << line;

	myFile >> line;
	if (line != ".") {
		temp = stoi(line);
	}
	myFile.ignore(100, '\n');

	cout << "Destination: " << line << endl;

	if (line != ".") {
		userMap->AddEdge(origin, temp);		// Add edge to and from origin
	}

	origin = temp;							// Replace destination with origin
	cout << "Origin: " << origin;

	myFile >> line;
	if (line != ".") {
		temp = stoi(line);
	}
	myFile.ignore(100, '\n');

	cout << "Destination: " << line << endl;

	if (line != ".") {
		userMap->AddEdge(origin, temp);		// Add edge to and from origin
	}

	if (boards == 4) {						// Do this process again if we need to connect 4 maps
		origin = temp;						// Replace destination with origin
		cout << "Origin: " << origin;

		myFile >> line;
		if (line != ".") {
			temp = stoi(line);
		}
		myFile.ignore(100, '\n');

		cout << "Destination: " << temp << endl;

		if (line != ".") {
			userMap->AddEdge(origin, temp);		// Add edge to and from origin
		}
	}
	
	// Let's print our map!
	cout << *userMap;
	
	// Validate it!
	cout << "Map validate() result: " << userMap->Validate() << endl;
	
	delete userMap;
	delete[] regions;
	regions = nullptr;
	
	myFile.close();
	
}

MapLoader::~MapLoader() {
	delete[] regions;
}

std::ostream& operator<<(std::ostream& strm, const MapLoader& file)
{
	return strm << "MapLoader(" << file.userFileName << ")";
}
