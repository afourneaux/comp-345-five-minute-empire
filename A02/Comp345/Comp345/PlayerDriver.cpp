#include <iostream>
#include "Player.h"
#include "Map.h"
using namespace std;



int testPlayer()
{
	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
	cout << "      TESTING PLAYER CLASS     " << endl;
	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;

	string lastName = "";
	const int numOfPlayers = 2;
	const int numOfTurns = 13;
	int currentTurn = 0;

	//Instantiating a Test Map
	int* arr = new int[4];
	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 1;
	arr[3] = 0;
	Map* testMap = new Map(arr, 4, 2, 2);
	delete[] arr;

	//Instantiating Test Players
	static vector<Player*> round_table[NUM_OF_PLAYERS];

	//Getting lastname of players
	for (int i = 0; i < numOfPlayers; i++) {
		cout << "Enter the name of Player " << i + 1 << ": ";
		cin >> lastName;
		round_table[i].at(i)->setLastName(lastName);
	}
	cout << endl << "Players for this game are: " << endl;
	for (int j = 0; j < numOfPlayers; j++) {
		cout << j + 1 << ". " << round_table->at(j)->GetLastName() << endl;
	}
	cout << endl;

	round_table->at(0)->PlaceNewArmies();
	round_table->at(0)->PlaceNewArmies();
	round_table->at(0)->MoveArmies();
	round_table->at(0)->BuildCity();
	round_table->at(0)->PlaceNewArmies();
	round_table->at(1)->PlaceNewArmies();
	round_table->at(1)->DestroyArmy();
	
	delete testMap;
	delete[] round_table;
	return 0;
}