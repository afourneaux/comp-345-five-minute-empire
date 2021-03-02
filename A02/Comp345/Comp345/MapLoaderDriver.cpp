#pragma once
#include "MapLoader.h"
#include <iostream>

using namespace std;

void Test() {
	MapLoader* test = new MapLoader("Map3.txt");
	test->readFile();
	test->buildMap(test->regions, test->regionsSize, test->players, test->continents);
}

//int mapLoaderTest(){
int main(){
	cout << endl << endl;
	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
	cout << "TESTING MAP LOADER CLASS" << endl;
	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;

	try {
		Test();
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
	return 0;
}