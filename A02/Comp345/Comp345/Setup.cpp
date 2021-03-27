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

SetupObj::SetupObj()
{
	invalid = true;
	mapInput = "";
	playerName = "";
	path = ".\\Maps\\";
}

//------------------------------------------//
//-------- DECIDE NUMBER OF PLAYERS --------//
//------------------------------------------//
void SetupObj::RequestPlayers() {
	invalid = true;							// Reset value
	do {
		cout << "\n(Number of players must be between 2 and 4)" << endl;
		cout << "Input number of players and press [ENTER]: ";
		cin >> MasterGame->playerCount;
		if (MasterGame->playerCount >= 2) {		// To make sure # of players is between 2 & 4
			if (MasterGame->playerCount <= 4) {
				invalid = false;
			}
		}
	} while (invalid);
}



//------------------------------------------//
//------------ CREATE PLAYERS --------------//
//------------------------------------------//
void SetupObj::MakePlayers() {
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

	//If 2-player game, also create a neutral player
	if (MasterGame->playerCount == 2) {
		player = new Player();
		player->SetLastName("NeutralPlayer");
		player->setPosition(2);
		player->neutralPlayer = true;
		MasterGame->players.push_back(player);
	}

	//Display players playing in this game
	cout << endl << "Players for this game are: " << endl;
	for (int j = 0; j < MasterGame->playerCount; j++) {
		cout << j + 1 << ". " << MasterGame->players[j]->GetLastName() << endl;
	}
}



//------------------------------------------//
//--------- DISPLAY LIST OF MAPS -----------//
//------------------------------------------//
void SetupObj::DisplayMaps() {
	cout << endl << "Here's a list of maps you can choose from: " << endl;
	mapInput = "";							// to store map names
	mapChoice = 0;							// to store map choice
	for (const auto& entry : filesystem::directory_iterator(path)) {
		mapInput = (entry.path()).string();	// to turn path into string
		mapInput = mapInput.substr(7);		// to exclude everything, but the filename
		mapNames.push_back(mapInput);		// to store the map names into vectors
		cout << mapChoice++ << " => " << mapInput << endl;
	}
}



//------------------------------------------//
//------ REQUEST & CREATE VALID MAP --------//
//------------------------------------------//
void SetupObj::MakeMap() {
	//Reset values
	invalid = true;
	mapInput = "";
	mapChoice = -1;
	do {
		cout << endl << "Type in the map number you'd like to play with (example: type 0 for " << mapNames[0] << "): ";
		cin >> mapInput;

		cout << endl << "Running map..." << endl;

		mapChoice = stoi(mapInput);						// to parse the string input into an int
		mapInput = mapNames[mapChoice];					// to select the map from the array
		MapLoader* mapObject = new MapLoader(mapInput);	// instantiate map
		mapObject->readFile();							// read mapfile

		// This conditional verifies that 
		if ((mapObject->players == 3 && (MasterGame->playerCount == 2 || MasterGame->playerCount == 3)) || (mapObject->players == 4 && MasterGame->playerCount == 4) || (mapObject->players > 4 || mapObject->players < 2)) {
			MasterGame->map = mapObject->buildMap(mapObject->regions, mapObject->regionsSize, mapObject->players, mapObject->continents);
			if (mapObject->validity == 0) {
				cout << endl << "Sorry, this map version is INVALID. Choose another map." << endl;
				delete mapObject;
				invalid = true;
			}
			else {
				invalid = false;
			}
		}
		else {
			cout << endl << "Sorry, this map version doesn't allow for your NUMBER OF PLAYERS: " << MasterGame->playerCount << ". Choose another map." << endl;
			delete mapObject;
			invalid = true;
		}
	} while (invalid);
}