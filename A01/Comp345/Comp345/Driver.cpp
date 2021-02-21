// Used to check for memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#include <iostream>
#include "Map.h"
#include "Cards.h"
#include "Player.h"
#include "Biding.h"

int main() {
	
	TestMap();
	TestCards();
	test_BiddingMain();

	//Check for memory leaks at the end of execution
	_CrtDumpMemoryLeaks();
}
