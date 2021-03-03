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
	Player* table = new Player[numOfPlayers];

	//Getting lastname of players
	for (int i = 0; i < numOfPlayers; i++) {
		cout << "Enter the name of Player " << i + 1 << ": ";
		cin >> lastName;
		table[i].setLastName(lastName);
	}
	cout << endl << "Players for this game are: " << endl;
	for (int j = 0; j < numOfPlayers; j++) {
		cout << j + 1 << ". " << table[j].GetLastName() << endl;
	}
	cout << endl;
	
	delete testMap;
	delete[] table;
	return 0;
}