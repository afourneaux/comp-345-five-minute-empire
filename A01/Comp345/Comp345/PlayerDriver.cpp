#include <iostream>;
#include "Player.h";
#include "Map.h";
using namespace std;

int main() 
{
	string lastName = "";
	int numOfPlayers = 2;

	//Opening the board game
	int* arr = new int[4];
	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 1;
	arr[3] = 0;
	Map* testMap = new Map(arr, 4, 2, 2);

	//Players sit at the table
	Player* table = new Player[numOfPlayers];
	Player player1 = table[0];
	Player player2 = table[1];

	//Prompting players for last name
	for (int i = 0; i < numOfPlayers; i++) {
		cout << "Enter the name of Player " << i+1 << ": ";
		cin >> lastName;
		table[i] = Player();
		table[i].setLastName(lastName);
	}
	cout << endl << "Players for this game are: " << endl;
	for (int j = 0; j < numOfPlayers; j++) {
		cout << j+1 << ". " << table[j].getLastName() << endl;
	}
	cout << endl;
	//Testing variables
	Territory* testLocation;
	Territory* testLocation2;
	Territory* testLocation3;
	Territory* testLocation4;
	int testPayment;
	int testID; //placeNewArmy
	int testID2; //moveArmy
	int testID3; //moveOverLand
	int testID4; // buildCity


	//testing PayCoins
	cout << "Testing payCoins method..." << endl;
	cout << "P1: How many coins would you like to Pay? ";
	cin >> testPayment;
	table[0].PayCoin(testPayment);
	cout << endl;
	
	//testing placeNewArmy
	cout << "Testing placeNewArmy method..." << endl;
	cout << "P1: Where would you like to place a new army? (integer) ";
	cin >> testID;
	testLocation = testMap->getTerritory(testID);
	player1.PlaceNewArmies(testLocation);
	cout << endl;

	//testing moveArmy
	cout << "Testing moveArmy method..." << endl;
	cout << "P1: Where would you like to move army at territoryID " << testID << " to (integer)? ";
	cin >> testID2;
	testLocation2 = testMap->getTerritory(testID2);
	player1.MoveArmies(testLocation, testLocation2);
	cout << endl;


	//testing moveOverLand
	//testing moveArmy
	cout << "Testing moveOverLand method..." << endl;
	cout << "P1: Where would you like to move army at territoryID " << testID2 << " to (integer)? ";
	cin >> testID3;
	testLocation3 = testMap->getTerritory(testID3);
	player1.MoveOverLand(testLocation2, testLocation3);
	cout << endl;


	
	//testing buildCity
	cout << "Testing buildCity method..." << endl;
	cout << "P1: Where would you like to build a city? (0, 1 are empty) ";
	cin >> testID4;
	testLocation4 = testMap->getTerritory(testID4);
	player1.BuildCity(testLocation4);
	cout << endl;

	//testing buildCity2
	cout << "Testing buildCity method..." << endl;
	cout << "P1: Where would you like to build a city? (0, 1 are empty) ";
	cin >> testID4;
	testLocation4 = testMap->getTerritory(testID4);
	player1.BuildCity(testLocation4);
	cout << endl;

	//testing destroyArmy
	cout << "Testing destroyArmy method..." << endl;
	cout << "P1: Destroying army from ID 3 (ally) with ID 2 (ennemy)? (integer) ";
	Territory* testLocation5 = testMap->getTerritory(2);
	player1.MoveArmies(testLocation4, testLocation5);
	
}