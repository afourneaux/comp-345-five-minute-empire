#include "Game.h"



void TestScoreCalculation() {
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
	
	for (int j = 0; j < 2; j++) {
		cout << "Printing player " << j << " hand contents: " << endl;
		for (int i = 0; i < MasterGame->players[j]->getHand().size(); i++) {
			cout << *MasterGame->players[j]->getHand().at(i);
		}
		cout << endl << endl;
	}

	cout << "Printing map: " << endl;
	cout << *MasterGame->map << endl;
	

	//test the score computation
	MasterGame->GetWinner();
	delete MasterGame;
	MasterGame = nullptr;

}