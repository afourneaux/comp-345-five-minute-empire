#include "ComputeScore.h"

using namespace std;

void ComputeScore(Map* map, Player* players, int player_count) {
	//Calculate the scores for controlled continents + territories
	int* final_scores = map->ComputeMapScores();

	int* elixir_count = new int[player_count];
	for (int i = 0; i < player_count; i++) elixir_count[i] = 0;

	//Loop through each player
	for (int player_index = 0; player_index < player_count; player_index++) {
		vector<Card*> hand = players[player_index].getHand();
		//Loop through each card player owns
		for (int card_index = 0; card_index < hand.size(); card_index++) {
			//loop through each ability on each card
			for (int ability_index = 0; ability_index < hand[card_index] ->abilityCount; ability_index++) {
				Ability* ability = &hand[card_index]->abilities[ability_index];
				if (ability->type == eAbility_Elixir)
					elixir_count[player_index]++;
				//If the card grants VP per cardName, count the number of cards with that name
				else if (ability->type == eAbility_VpPerCardName) {
					int count = 0;
					for (int i = 0; i < hand.size(); i++) {
						if (hand[i]->name.find(ability->setName) != string::npos) {
							count++;
						}
					}
					if (count >= ability->setTarget) {
						if (ability->countSetOnce)
							final_scores[player_index] += ability->value;
						else
							final_scores[player_index] += ability->value * count;
					}
				}
				else if (ability->type == eAbility_VpPerCoins) {
					final_scores[player_index] += (players[player_index].getCoins() / ability->setTarget) * ability->value;
				}
			}
		}
	}
	int elixir_winner = -1;
	int elixir_max = -1;
	for (int i = 0; i < player_count; i++) {
		if (elixir_count[i] > elixir_max) {
			elixir_winner = i;
			elixir_max = elixir_count[i];
		}
		else if (elixir_count[i] == elixir_max) {
			elixir_winner = -1;
		}
	}

	final_scores[elixir_winner] += ELIXIR_BONUS;
	delete[] elixir_count;

	cout << "FINAL SCORES" << endl;
	for (int i = 0; i < player_count; i++) {
		cout << "Player " << i << " total score " << final_scores[i] << endl;
	}

}


void TestComputeScore() {	
	int* arr = new int[4];
	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 1;
	arr[3] = 0;
	Map* testMap = new Map(arr, 4, 2, 2);
	testMap->AddEdge(0, 1);
	testMap->AddEdge(0, 2);
	testMap->AddEdge(0, 3);
	testMap->AddEdge(1, 3);
	testMap->AddEdge(1, 2);
	testMap->AddEdge(2, 3);

	//Instantiating Test Players
	Player* table = new Player[2];

	table[0].setLastName("Bob Loblaw");
	table[0].setPosition(0);
	table[1].setLastName("John Smith");
	table[1].setPosition(1);
	table[0].PlaceNewArmies(testMap->GetTerritory(0));
	table[0].PlaceNewArmies(testMap->GetTerritory(1));
	table[0].PlaceNewArmies(testMap->GetTerritory(1));
	table[0].PlaceNewArmies(testMap->GetTerritory(1));
	table[0].PlaceNewArmies(testMap->GetTerritory(2));

	table[1].PlaceNewArmies(testMap->GetTerritory(0));
	table[1].PlaceNewArmies(testMap->GetTerritory(3));
	table[1].PlaceNewArmies(testMap->GetTerritory(1));
	table[1].PlaceNewArmies(testMap->GetTerritory(1));
	table[1].PlaceNewArmies(testMap->GetTerritory(3));

	table[0].BuildCity(testMap->GetTerritory(0));
	table[1].BuildCity(testMap->GetTerritory(0));
	table[1].BuildCity(testMap->GetTerritory(3));

	cout << *testMap;

	Deck* deck = new Deck();
	Hand* hand = new Hand(deck);

	table[0].getHand().push_back(hand->Exchange(0, table[0]));
	table[0].getHand().push_back(hand->Exchange(0, table[0]));
	table[1].getHand().push_back(hand->Exchange(0, table[1]));
	table[1].getHand().push_back(hand->Exchange(0, table[1]));

	ComputeScore(testMap, table, 2);

}
