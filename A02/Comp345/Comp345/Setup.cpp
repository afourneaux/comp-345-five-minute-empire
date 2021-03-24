#pragma once
#include "MapLoader.h"
#include "Player.h"
#include "Cards.h"
#include <iostream>
#include <string>
#include <filesystem>
#include "Setup.h"
#include "Game.h"

using namespace std;

Setup::Setup()
{
	invalid = true;
	mapInput = "";
	playerName = "";
	path = ".\\Maps\\";
}

//------------------------------------------//
//-------- DECIDE NUMBER OF PLAYERS --------//
//------------------------------------------//
void Setup::RequestPlayers() {
	invalid = true;							// Reset value
	do {
		cout << "\n(Number of players must be between 2 and 4)" << endl;
		cout << "Input number of players and press [ENTER]: ";
		cin >> MasterGame->playerCount;
		if (MasterGame->playerCount >= 2) {
			if (MasterGame->playerCount <= 4) {
				invalid = false;
			}
		}
	} while (invalid);
}



//------------------------------------------//
//------------ CREATE PLAYERS --------------//
//------------------------------------------//
void Setup::MakePlayers() {
	Player* player;
	// Getting player names
	for (int i = 0; i < MasterGame->playerCount; i++) {
		player = new Player();
		cout << "Enter the name of Player " << i + 1 << ": ";
		cin >> playerName;
		player->SetLastName(playerName);
		player->setPosition(i);
		MasterGame->players.push_back(player);
	}
	cout << endl << "Players for this game are: " << endl;
	for (int j = 0; j < MasterGame->playerCount; j++) {
		cout << j + 1 << ". " << MasterGame->players[j]->GetLastName() << endl;
	}
}



//------------------------------------------//
//--------- DISPLAY LIST OF MAPS -----------//
//------------------------------------------//
void Setup::DisplayMaps() {
	cout << "Here's a list of maps you can choose from: " << endl;

	//string path = ".\\Maps\\";
	for (const auto& entry : filesystem::directory_iterator(path)) {
		cout << entry.path() << endl;
	}
}



//------------------------------------------//
//------ REQUEST & CREATE VALID MAP --------//
//------------------------------------------//
void Setup::MakeMap() {
	invalid = true;							// Reset value
	do {
		cout << endl << "Type in the name of the map file you'd like to play with (example: Map2a.txt): ";
		cin >> mapInput;

		cout << endl << "Running map..." << endl;

		MapLoader* mapObject = new MapLoader(mapInput);
		mapObject->readFile();
		if (mapObject->players != MasterGame->playerCount) {
			cout << "Sorry, this map version is only for " << MasterGame->playerCount << "players. Choose another map." << endl;
			delete mapObject;
			invalid = true;
		}
		else {
			mapObject->buildMap(mapObject->regions, mapObject->regionsSize, mapObject->players, mapObject->continents);
			if (mapObject->validity == 0) {
				cout << "Sorry, this map version in invalid. Choose another map." << endl;
				delete mapObject;
				invalid = true;
			}
			else {
				invalid = false;
			}
		}
	} while (invalid);
}