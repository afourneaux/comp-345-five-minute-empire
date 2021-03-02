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
	testMap->AddEdge(0, 1);
	testMap->AddEdge(0, 2);
	testMap->AddEdge(0, 3);
	testMap->AddEdge(1, 3);
	testMap->AddEdge(1, 2);
	testMap->AddEdge(2, 3);
	delete[] arr;

	//Instantiating Test Players
	static vector<Player*> round_table[NUM_OF_PLAYERS];

	//Getting lastname of players
	for (int i = 0; i < numOfPlayers; i++) {
		cout << "Enter the name of Player " << i + 1 << ": ";
		cin >> lastName;
<<<<<<< HEAD
		round_table[i].at(i)->setLastName(lastName);
=======
		table[i].setLastName(lastName);
		table[i].setPosition(i);
>>>>>>> origin/a2-map_player_sync
	}
	cout << endl << "Players for this game are: " << endl;
	for (int j = 0; j < numOfPlayers; j++) {
		cout << j + 1 << ". " << round_table->at(j)->GetLastName() << endl;
	}
	cout << endl;

<<<<<<< HEAD
	round_table->at(0)->PlaceNewArmies();
	round_table->at(0)->PlaceNewArmies();
	round_table->at(0)->MoveArmies();
	round_table->at(0)->BuildCity();
	round_table->at(0)->PlaceNewArmies();
	round_table->at(1)->PlaceNewArmies();
	round_table->at(1)->DestroyArmy();
	
=======
	//Testing variables
	Territory* testLocation;
	Territory* testLocation2;
	int payment; // payCoins()
	int testID;
	int testID2;

	//testing payCoins()
	cout << "-------------------------------------------------" << endl;
	cout << "         Testing payCoins(): Enough money        " << endl;
	cout << "-------------------------------------------------" << endl;
	table[0].PayCoin(5);
	cout << endl;

	cout << "-------------------------------------------------" << endl;
	cout << "    Testing payCoins(): Exactly enough money     " << endl;
	cout << "-------------------------------------------------" << endl;
	table[1].PayCoin(14);
	cout << endl;

	cout << "-------------------------------------------------" << endl;
	cout << "       Testing payCoins(): Not Enough money      " << endl;
	cout << "-------------------------------------------------" << endl;
	table[0].PayCoin(10);
	cout << endl;

	cout << table[0];
	cout << table[1];

	//testing placeNewArmy
	cout << "-------------------------------------------------" << endl;
	cout << "      Testing placeNewArmy(): Valid entry (1)    " << endl;
	cout << "-------------------------------------------------" << endl;
	testLocation = testMap->GetTerritory(1);
	table[0].PlaceNewArmies(testLocation);
	cout << endl;

	cout << "-------------------------------------------------" << endl;
	cout << "   Testing placeNewArmy(): Non-Valid entry (6)   " << endl;
	cout << "-------------------------------------------------" << endl;
	testLocation = testMap->GetTerritory(6);
	table[0].PlaceNewArmies(testLocation);
	cout << endl;

	cout << table[0];
	cout << table[1];

	//testing moveArmy
	cout << "-------------------------------------------------" << endl;
	cout << "      Testing moveArmy(): Valid entry (1->2)     " << endl;
	cout << "-------------------------------------------------" << endl;
	testLocation = testMap->GetTerritory(1);
	testLocation2 = testMap->GetTerritory(2);
	table[0].MoveArmies(testLocation, testLocation2);
	cout << endl;

	cout << "-------------------------------------------------" << endl;
	cout << "    Testing moveArmy(): Non-Valid entry (1->2)   " << endl;
	cout << "-------------------------------------------------" << endl;
	testLocation = testMap->GetTerritory(1);
	testLocation2 = testMap->GetTerritory(2);
	table[0].MoveArmies(testLocation, testLocation2);
	cout << endl;

	cout << table[0];
	cout << table[1];

	//testing moveOverLand
	cout << "-------------------------------------------------" << endl;
	cout << "    Testing moveOverLand(): Valid entry (1->2)   " << endl;
	cout << "-------------------------------------------------" << endl;
	testLocation = testMap->GetTerritory(1);
	testLocation2 = testMap->GetTerritory(2);
	table[0].MoveOverLand(testLocation, testLocation2);
	cout << endl;

	cout << "-------------------------------------------------" << endl;
	cout << "  Testing moveOverLand(): Non-Valid entry (1->2) " << endl;
	cout << "-------------------------------------------------" << endl;
	testLocation = testMap->GetTerritory(1);
	testLocation2 = testMap->GetTerritory(2);
	table[0].MoveOverLand(testLocation, testLocation2);
	cout << endl;

	cout << table[0];
	cout << table[1];

	//testing buildCity
	cout << "-------------------------------------------------" << endl;
	cout << "        Testing buildCity(): Valid (2)      " << endl;
	cout << "-------------------------------------------------" << endl;
	testLocation = testMap->GetTerritory(2);
	table[0].BuildCity(testLocation);
	cout << endl;

	cout << "-------------------------------------------------" << endl;
	cout << "          Testing buildCity(): Non-Valid (1)        " << endl;
	cout << "-------------------------------------------------" << endl;
	testLocation = testMap->GetTerritory(0);
	table[0].BuildCity(testLocation);
	cout << endl;

	cout << table[0];
	cout << table[1];

	//testing destroyArmy
	cout << "--------------------------------------------------" << endl;
	cout << "        Testing destroyArmy() -> Prompting        " << endl;
	cout << "--------------------------------------------------" << endl;
	cout << table[0].GetLastName() << ", where would you like to place an army: ";
	cin >> testID;
	cout << table[1].GetLastName() << ", where would you like to place an army: ";
	cin >> testID2;
	testLocation = testMap->GetTerritory(testID);
	testLocation2 = testMap->GetTerritory(testID2);
	table[0].PlaceNewArmies(testLocation);
	table[1].PlaceNewArmies(testLocation2);
	table[0].DestroyArmy(testLocation, testLocation2, &table[1]);

	cout << table[0];
	cout << table[1];

	cout << *testMap;

>>>>>>> origin/a2-map_player_sync
	delete testMap;
	delete[] round_table;
	return 0;
}