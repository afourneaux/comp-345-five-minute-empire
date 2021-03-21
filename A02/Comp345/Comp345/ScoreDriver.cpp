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
		cout << "Exchanged card: " << *card << endl;
		MasterGame->players[i % 2]->AddCardToHand(card);
		cout<< "Card in hand" << *MasterGame->players[i % 2]->getHand().back() << endl;
	}
	cout << "Printing player 0 hand contents: " << endl;
	for (int i = 0; i < MasterGame->players[0]->getHand().size(); i++) {
		cout << *MasterGame->players[0]->getHand().at(i);
	}

	//test the score computation
	MasterGame->GetWinner();

}