// Used to check for memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>

#include "Map.h"
#include "MapLoader.h"
#include "Cards.h"
#include "Player.h"
#include "BiddingFacility.h"

int main() {
	//TestMap();
	//mapLoaderTest();
	//testPlayer();
	TestCards();
	TestBiddingFacility();

	//Check for memory leaks at the end of execution
	_CrtDumpMemoryLeaks();
}
