// COMP345 Assignment 1
// Map class driver
// Author: Georges Grondin (40034160)

#include "Map.h"
#include <iostream>

using namespace std;

int TestMap() {

	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
	cout << "TESTING MAP CLASS" << endl;
	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "Test case 1: map with non-connected node" << endl;
	cout << "---------------------------------------------------" << endl;
	int* arr = new int[4];
	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 1;
	arr[3] = 0;
	Map* testMap = new Map(arr, 4, 2, 2);
	testMap->AddEdge(0, 2);
	testMap->AddEdge(2, 3);
	testMap->AddEdge(0, 3);
	cout << *testMap;
	cout << "Map validate() result: " << testMap->Validate() << endl << endl;
	delete testMap;

	cout << "---------------------------------------------------" << endl;
	cout << "Test case 2: map with non-connected node clusters" << endl;
	cout << "---------------------------------------------------" << endl;
	testMap = new Map(arr, 4, 2, 2);
	testMap->AddEdge(0, 1);
	testMap->AddEdge(2, 3);
	cout << *testMap;
	cout << "Map validate() result: " << testMap->Validate() << endl << endl;
	delete testMap;

	cout << "---------------------------------------------------" << endl;
	cout << "Test case 3: map with non-contiguous continent  (Territories 1 and 2 belong to the same continent but not directly connected)" << endl;
	cout << "---------------------------------------------------" << endl;
	testMap = new Map(arr, 4, 2, 2);
	testMap->AddEdge(0, 1);
	testMap->AddEdge(0, 2);
	testMap->AddEdge(0, 3);
	testMap->AddEdge(1, 3);
	testMap->AddEdge(2, 3);
	cout << *testMap;
	cout << "Map validate() result: " << testMap->Validate() << endl << endl;
	delete testMap;

	cout << "---------------------------------------------------" << endl;
	cout << "Test case 4: map with a one-way edge" << endl;
	cout << "---------------------------------------------------" << endl;
	testMap = new Map(arr, 4, 2, 2);
	testMap->AddEdge(0, 1);
	testMap->AddEdge(0, 2);
	testMap->AddEdge(0, 3);
	testMap->AddEdge(1, 3);
	testMap->AddEdge(1, 2);
	testMap->AddEdge(2, 3);
	//Edges are added bi-directionally by default. To test a fail case, manually delete an edge
	Edge* edge_to_delete = testMap->GetTerritory(0)->head;
	testMap->GetTerritory(0)->head = testMap->GetTerritory(0)->head->next;
	delete edge_to_delete;
	cout << *testMap;
	cout << "Map validate() result: " << testMap->Validate() << endl << endl;
	delete testMap;

	cout << "---------------------------------------------------" << endl;
	cout << "Test case 5: valid map" << endl;
	cout << "---------------------------------------------------" << endl;
	testMap = new Map(arr, 4, 2, 2);
	testMap->AddEdge(0, 1);
	testMap->AddEdge(0, 2);
	testMap->AddEdge(0, 3);
	testMap->AddEdge(1, 3);
	testMap->AddEdge(1, 2);
	testMap->AddEdge(2, 3);
	cout << *testMap;
	cout << "Map validate() result: " << testMap->Validate() << endl << endl;

	cout << "---------------------------------------------------" << endl;
	cout << "Test case 6: copy constructor: copying previous map, deleting it and printing:" << endl;
	cout << "---------------------------------------------------" << endl;
	Map* copyMap = new Map(testMap);
	delete testMap;
	cout << *copyMap << endl;

	testMap = new Map(arr, 4, 2, 2);
	testMap->AddEdge(0, 1);
	testMap->AddEdge(0, 2);
	testMap->AddEdge(0, 3);
	testMap->AddEdge(1, 3);
	testMap->AddEdge(1, 2);
	testMap->AddEdge(2, 3);

	cout << "---------------------------------------------------" << endl;
	cout << "Test case 7: assignment operator: assigning map, deleting input map and printing:" << endl;
	cout << "---------------------------------------------------" << endl;
	*copyMap = *testMap;
	delete testMap;
	cout << *copyMap << endl;
	
	delete copyMap;
	delete[] arr;

	return 0;
}
