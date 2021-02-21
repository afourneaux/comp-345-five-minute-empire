#pragma once
#include "MapLoader.h"
#include <iostream>

using namespace std;

void Test() {
	MapLoader* test = new MapLoader("Map3.txt");
}

int main(){
	try {
		Test();
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
	return 0;
}