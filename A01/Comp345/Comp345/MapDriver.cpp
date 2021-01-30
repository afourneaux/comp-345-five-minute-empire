#include "Map.h"
#include <iostream>

using namespace std;

int testMap() {
	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
	cout << "TESTING MAP CLASS" << endl;
	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;\
	cout << "---------------------------------------------------" << endl;
	cout << "Test case 1: map with non-connected node" << endl;
	cout << "---------------------------------------------------" << endl;
	int* arr = new int[4];
	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 1;
	arr[3] = 0;
	Map* testMap = new Map(arr, 4, 2, 2);
	testMap->addEdge(0, 2);
	testMap->addEdge(2, 3);
	testMap->addEdge(0, 3);
	testMap->printMap();
	cout << "Map validate() result: " << testMap->validate() << endl;
	delete testMap;

	cout << "---------------------------------------------------" << endl;
	cout << "Test case 2: map with non-connected node clusters" << endl;
	cout << "---------------------------------------------------" << endl;
	testMap = new Map(arr, 4, 2, 2);
	testMap->addEdge(0, 1);
	testMap->addEdge(2, 3);
	testMap->printMap();
	cout << "Map validate() result: " << testMap->validate() << endl;
	delete testMap;

	cout << "---------------------------------------------------" << endl;
	cout << "Test case 3: map with non-contiguous continent  (Territories 1 and 2 belong to the same continent but not directly connected)" << endl;
	cout << "---------------------------------------------------" << endl;
	testMap = new Map(arr, 4, 2, 2);
	testMap->addEdge(0, 1);
	testMap->addEdge(0, 2);
	testMap->addEdge(0, 3);
	testMap->addEdge(1, 3);
	testMap->addEdge(2, 3);
	testMap->printMap();
	cout << "Map validate() result: " << testMap->validate() << endl;
	delete testMap;

	cout << "---------------------------------------------------" << endl;
	cout << "Test case 4: valid map" << endl;
	cout << "---------------------------------------------------" << endl;
	testMap = new Map(arr, 4, 2, 2);
	testMap->addEdge(0, 1);
	testMap->addEdge(0, 2);
	testMap->addEdge(0, 3);
	testMap->addEdge(1, 3);
	testMap->addEdge(1, 2);
	testMap->addEdge(2, 3);
	testMap->printMap();
	cout << "Map validate() result: " << testMap->validate() << endl;
	delete testMap;
	delete[] arr;

	return 0;
}
