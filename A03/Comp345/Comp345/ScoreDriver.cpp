#include "Game.h"


// Slightly contrived demo function that demonstrates final score calculation without requiring an entire game to be played
void TestScoreCalculation() {
	//initial game Setup
	MasterGame = new Game();
	MasterGame->Setup();
	//populate map with some armies/cities
	for (int i = 0; i < MasterGame->map->territory_count; i++) {
		MasterGame->map->GetTerritory(i)->addArmy(0);
		if (i % 2 == 0) {
			MasterGame->map->GetTerritory(i)->addArmy(1);
			MasterGame->map->GetTerritory(i)->addArmy(1);
		}
		if (i % 3 == 0) {
			MasterGame->map->GetTerritory(i)->addCity(1);
		}
		if (i % 5 == 0) {
			MasterGame->map->GetTerritory(i)->addCity(0);
		}
	}

	//populate players with some cards
	for (int i = 0; i < 18; i++) {
		Card* card = MasterGame->GetHand()->Exchange(0);
		MasterGame->players[i % 2]->AddCardToHand(card);
	}
	

	// Print the "final" game state: player hand contents and map
	for (int j = 0; j < 2; j++) {
		cout << "Printing player " << j << " hand contents: " << endl;
		for (int i = 0; i < MasterGame->players[j]->GetHand().size(); i++) {
			cout << *MasterGame->players[j]->GetHand().at(i);
		}
		cout << endl << endl;
	}
	cout << "Printing map: " << endl;
	cout << *MasterGame->map << endl;
	

	//do the score computation
	MasterGame->GetWinner();
	delete MasterGame;
	MasterGame = nullptr;

}