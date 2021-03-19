#pragma once
#include <iostream>
#include <string>
#include "MapLoader.h"
#include "Player.h"

using namespace std;

int main() {
	//------------------------------------------//
	//------------- MAP VARIABLES --------------//
	//------------------------------------------//
	int numOfPlayers = 2;						// Number of players (2, 3, 4)
	char mapVersion = 'a';						// Map version (a, b)
	bool invalid = true;						// true for invalid, false for valid
	string mapInput;							// Stores the name of the map to be ran

	//----------- ------------------------------//
	//------------ PLAYER VARIABLES ------------//
	//------------------------------------------//
	string playerName = "";						// Container for a player's name

	cout << endl;
	cout << "#----------------------------------#" << endl;
	cout << "#            MAIN MENU             #" << endl;
	cout << "#----------------------------------#" << endl;

	//----------- ------------------------------//
	//-------- DECIDE NUMBER OF PLAYERS --------//
	//------------------------------------------//
	do {
		cout << "\n(Number of players must be between 2 and 4)" << endl;
		cout << "Input number of players and press [ENTER]: ";
		cin >> numOfPlayers;
		if (numOfPlayers >= 2) {
			if (numOfPlayers <= 4) {
				invalid = false;
			}
		}
	} while (invalid);
	
	cout << endl;

	//------------------------------------------//
	//------------ CREATE PLAYERS --------------//
	//------------------------------------------//
	Player* table = new Player[numOfPlayers];	// Instantiating players

	// Getting player names
	for (int i = 0; i < numOfPlayers; i++) {
		cout << "Enter the name of Player " << i + 1 << ": ";
		cin >> playerName;
		table[i].setLastName(playerName);
	}
	cout << endl << "Players for this game are: " << endl;
	for (int j = 0; j < numOfPlayers; j++) {
		cout << j + 1 << ". " << table[j].GetLastName() << endl;
	}

	//------------------------------------------//
	//---------- DECIDE MAP VERSION ------------//
	//------------------------------------------//
	invalid = true;								// Reset value

	do {
		cout << "\n(Map version must be either 'a' or 'b')" << endl;
		cout << "Input map version and press [ENTER]: ";
		cin >> mapVersion;
		if (mapVersion == 'a' || mapVersion == 'b') {
			invalid = false;
		}
	} while (invalid);

	cout << endl;

	mapInput = "Map" + to_string(numOfPlayers) + mapVersion + ".txt";

	//------------------------------------------//
	//-------------- CREATE MAP ----------------//
	//------------------------------------------//
	MapLoader* mapObject = new MapLoader(mapInput);
	mapObject->readFile();
	mapObject->buildMap(mapObject->regions, mapObject->regionsSize, mapObject->players, mapObject->continents);

	//cout << endl;

	//------------------------------------------//
	//---------- CREATE DECK & HAND ------------//
	//------------------------------------------//
	Deck* deck = new Deck();
	Hand* hand = new Hand(deck);

	/*IGNORE
	vector<Territory*> territories;
	vector<Cube*> cubes;
	vector<Disk*> disks;
	vector <Card*> hand;
	BiddingFacility* bf;
	int coins;
	int armiesLeft;

	territories = table[0].getTerritories();
	cubes = table[0].getCubes();
	disks = table[0].getDisks();
	//hand = table[0].getHand();
	bf = table[0].GetBf();
	coins = table[0].getCoins();
	armiesLeft = table[0].getArmiesLeft();

	table[1].getTerritories();
	table[1].getCubes();
	table[1].getDisks();
	table[1].getHand();
	table[1].GetBf();
	table[1].getCoins();
	table[1].getArmiesLeft();
	*/

	cout << "\nX X X X X X X X X X X X X X X X X X X" << endl;
	cout << "      INFORMATION ABOUT PLAYERS" << endl;
	cout << "X X X X X X X X X X X X X X X X X X X\n" << endl;

	cout << table[0];
	cout << table[1];

	/*IGNORE
	std::vector<int> input = territories;
	print(input);
	*/
}

/*IGNORE
void print(std::vector<int> const& input)
{
	for (int i = 0; i < input.size(); i++) {
		std::cout << input.at(i) << ' ';
	}
}
*/