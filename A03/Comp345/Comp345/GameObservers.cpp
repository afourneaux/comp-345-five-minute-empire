#include <iostream>
#include <algorithm>
#include <iomanip>
#include <Windows.h>
#include "GameObservers.h"
#include "Game.h"
#include<sstream>

Observer::Observer() {};
Observer::~Observer() {};

Subject::Subject() {
	observers = new list<Observer*>;
}

Subject::~Subject() {
	delete observers;
}

void Subject::Attach(Observer* obs) {
	observers->push_back(obs);
}

void Subject::Detach(Observer* obs) {
	observers->remove(obs);
}

void Subject::Notify() {
	list<Observer*>::iterator i = observers->begin();
	for (; i != observers->end(); ++i)
		(*i)->Update();
}


GameStateView::GameStateView() {
	game = nullptr;
};

GameStateView::GameStateView(Game* game) {
	this->game = game;
}

GameStateView::~GameStateView() {
}

void GameStateView::Update() {
	Display();
}

void GameStateView::Display() {
	// Recalculate all player scores on refresh
	// TODO: move this logic elsewhere
	for (int i = 0; i < game->playerCount; i++) {
		game->players[i]->ComputeScore();
	}

	system("CLS");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int maxLength = max(game->maxPlayerNameLength + 5, 15);
	cout << setiosflags(ios::left);

	//////////////////////////////////////////////////
	// PART 1: RENDER Game Statistics
	//////////////////////////////////////////////////
	cout << '+' << setfill('=') << setw(maxLength-1) << "=";
	cout << '+' << setfill(' ') << endl;
	cout << setw(maxLength) << "| PLAYER STATS";
	cout << '|' << endl;
	//Print horizontal divider
	cout << '+' << setfill('=') << setw(maxLength-1) << "=";
	for (int i = 0; i < STATS_COLUMN_COUNT; i++) {
		cout << '+';
		cout << setfill('=') << setw(STATS_COLUMN_WIDTH - 1) << "=";
	}
	cout << "+" << setfill(' ') << endl;
	//Print headers
	cout << left << setw(maxLength) << "| Player";
	cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << "Coins";
	cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << "# Territories";
	cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << "# Continents";
	cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << "# Elixirs";
	cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << "Army Bonus";
	cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << "Move Bonus";
	cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << "Flying Bonus";
	cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << "Immune";
	cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << "Card VPs";
	cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << "Total VP";
	cout << left << "|" << endl;
	//Print horizontal divider
	cout << '+' << setfill('=') << setw(maxLength-1) << "=";
	for (int i = 0; i < STATS_COLUMN_COUNT; i++) {
		cout << '+';
		cout << setfill('=') << setw(STATS_COLUMN_WIDTH - 1) << "=";
	}
	cout << "+" << setfill(' ') << endl;

	//Print player rows: player name + game stats
	for (int i = 0; i < game->players.size(); i++) {
		cout << '|' << right << setw(maxLength-1) << (game->players[i]->GetLastName() + " ");
		cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getCoins();
		cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getTerritoryScore();
		cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getContinentScore();
		if (game->players[i]->getElixirWinner()) {
			cout << left << "| ";
			SetConsoleTextAttribute(hConsole, 10); // Set colour to green for elixir winner
			cout << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getElixirs();
		}
		else {
			cout << left << "| ";
			SetConsoleTextAttribute(hConsole, 12); // Set colour to red for elixir loser
			cout << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getElixirs();
		}
		SetConsoleTextAttribute(hConsole, 15); // reset to White
		cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getBonusArmies();
		cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getBonusMoves();
		cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getBonusFlying();
		cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getBonusImmune();
		cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getCardScore();
		cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getTotalScore();

		cout << "|" << endl;
	}
	//Print horizontal divider
	cout << '+' << setfill('=') << setw(maxLength-1) << "=";
	for (int i = 0; i < STATS_COLUMN_COUNT; i++) {
		cout << '+';
		cout << setfill('=') << setw(STATS_COLUMN_WIDTH - 1) << "=";
	}
	cout << "+" << setfill(' ') << endl;

	//////////////////////////////////////////////////
	// PART 2: RENDER MAP
	//////////////////////////////////////////////////
	cout << '+' << setfill('=') << setw(maxLength-1) << "=";
	cout << '+' << setfill(' ') << endl;
	cout << setw(maxLength) << "| MAP";
	cout << '|' << endl;
	//Print horizontal divider
	cout << '+' << setfill('=') << setw(maxLength-1) << "=";
	for (int i = 0; i < game->map->territory_count; i++) {
		cout << '+';
		cout << setfill('=') << setw(MAP_COLUMN_WIDTH - 1) << "=";
	}
	cout << '+' << setfill(' ') << endl;

	//Print headers row 1: Territory/Continent labels
	cout << left << setw(maxLength) << "|";
	for (int i = 0; i < game->map->territory_count; i++) {
		cout << "| ";
		if (game->map->starting_territory_index == i)
			SetConsoleTextAttribute(hConsole, 14); // Set colour to yellow for starting territory
		else
			SetConsoleTextAttribute(hConsole, 15); // White otherwise
		string terr = "T" + to_string(i) + ", C" + to_string(game->map->territories[i].continentID);
		cout << left << setw(MAP_COLUMN_WIDTH - 2) << terr;
	}
	SetConsoleTextAttribute(hConsole, 15);  // Reset console colour
	cout << '|' << endl;

	//Print headers row 2: Player label + adjacent territories
	cout << left << setw(maxLength) << "| Player";
	for (int i = 0; i < game->map->territory_count; i++) {
		cout << left << "|->" ;
		int connections_str_length = 3;
		Edge* temp = game->map->territories[i].head;
		while (temp != nullptr) {
			if (temp->movement_cost == game->map->WATER_MOVEMENT_COST)
				SetConsoleTextAttribute(hConsole, 11); // set output colour to cyan if water connection
			else 
				SetConsoleTextAttribute(hConsole, 15); // White otherwise
			string conn = to_string(temp->destination_territory->territoryID) + " ";
			cout << left << conn;
			connections_str_length += conn.length();
			temp = temp->next;
		}
		cout << left << setw(MAP_COLUMN_WIDTH - connections_str_length) << " ";
		SetConsoleTextAttribute(hConsole, 15);
	}
	cout << '|' << endl;

	//Print horizontal divider
	cout << '+' << setfill('=') << setw(maxLength-1) << "=";
	for (int i = 0; i < game->map->territory_count; i++) {
		cout << '+';
		cout << setfill('=') << setw(MAP_COLUMN_WIDTH - 1) << "=";
	}
	cout << '+' << setfill(' ') << endl;

	//Print player rows: player name + city/army count per territory
	for (int i = 0; i < MasterGame->players.size(); i++) {
		cout << '|' << right << setw(maxLength-1) << (MasterGame->players[i]->GetLastName() + " ");
		for (int j = 0; j < game->map->territory_count; j++) {
			cout << "| ";
			if (game->map->territories[j].controlling_player == i)
				SetConsoleTextAttribute(hConsole, 10); // Set console colour to green for controlling player
			else
				SetConsoleTextAttribute(hConsole, 12); // Set console colour to red for non-controlling player
			string barGraph = "";
			cout << setw(10);
			for (int k = 0; k < game->map->territories[j].city_count[i]; k++)
				barGraph.append("C");
			//If the player has a lot of armies render compact version to avoid breaking columns alignment
			if (game->map->territories[j].army_count[i] > 7) {
				barGraph.append("Ax" + to_string(game->map->territories[j].army_count[i]));
			}
			else {
				for (int k = 0; k < game->map->territories[j].army_count[i]; k++)
					barGraph.append("A");
			}
			
			cout << left << setw(MAP_COLUMN_WIDTH - 2) << barGraph;
			SetConsoleTextAttribute(hConsole, 15); // Reset console colour
		}
		cout << '|' << endl;
	}

	//Print horizontal divider
	cout << '+' << setfill('=') << setw(maxLength-1) << "=";
	for (int i = 0; i < game->map->territory_count; i++) {
		cout << '+';
		cout << setfill('=') << setw(MAP_COLUMN_WIDTH - 1) << "=";
	}
	cout << '+' << setfill(' ') << endl;

	//////////////////////////////////////////////////
	// PART 3: RENDER DRAFTABLE CARDS 
	//////////////////////////////////////////////////

	cout << '+' << setfill('=') << setw(CARD_WIDTH - 1) << "=";
	cout << '+' << setfill(' ') << endl;
	cout << '|' << setw(CARD_WIDTH - 1) << " AVAILABLE CARDS";
	cout << '|' << endl;

	//Print horizontal divider
	for (int i = 0; i < HAND_SIZE; i++) {
		cout << '+';
		cout << setfill('=') << setw(CARD_WIDTH - 1) << "=";
	}
	cout << "+" << setfill(' ') << endl;
	//Print card index and cost
	for (int i = 0; i < HAND_SIZE; i++) {
		cout << left << setw(5) << ("| [" + to_string(i) + "]");
		cout << right << setw(CARD_WIDTH - 5) << ("Cost: " + to_string(game->GetHand()->GetCostAtIndex(i)) + " ");
	}
	cout << "|" << endl;
	//Print card name
	for (int i = 0; i < HAND_SIZE; i++) {
		cout << left << setw(CARD_WIDTH) << "| " + game->GetHand()->GetCardAtIndex(i)->name;
	}
	cout << "|" << endl;
	//Print horizontal divider
	for (int i = 0; i < HAND_SIZE; i++) {
		cout << '+';
		cout << setfill('=') << setw(CARD_WIDTH - 1) << "=";
	}
	cout << "+" << setfill(' ') << endl;
	
	stringstream ss;
	//Print card abilities
	for (int i = 0; i < HAND_SIZE; i++) {
		cout << "| " << left << setw(CARD_WIDTH - 2);
		for (int j = 0; j < game->GetHand()->GetCardAtIndex(i)->abilityCount; j++) {
			ss << game->GetHand()->GetCardAtIndex(i)->abilities[j];
			if (j < game->GetHand()->GetCardAtIndex(i)->abilityCount - 1)
				ss << ", ";
		}
		cout << ss.str();
		ss.str("");
	}
	cout << "|" << endl;
	//Print first card action
	for (int i = 0; i < HAND_SIZE; i++) {
		cout << "| " << left << setw(CARD_WIDTH - 2);
		ss << game->GetHand()->GetCardAtIndex(i)->actions[0];
		cout << ss.str();
		ss.str("");
	}
	
	cout << "|" << endl;
	//Print card and/or modifier if applicable
	for (int i = 0; i < HAND_SIZE; i++) {
		cout << "| " << left << setw(CARD_WIDTH - 2);
		if (game->GetHand()->GetCardAtIndex(i)->actionCount > 1) {
			if (game->GetHand()->GetCardAtIndex(i)->actionChoice == eChoice_And)
				cout << "AND";
			else if (game->GetHand()->GetCardAtIndex(i)->actionChoice == eChoice_Or)
				cout << "OR";
		}
		else
			cout << " ";
	}
	cout << "|" << endl;
	//Print card action 2 if applicable
	for (int i = 0; i < HAND_SIZE; i++) {
		cout << "| " << left << setw(CARD_WIDTH - 2);
		if (game->GetHand()->GetCardAtIndex(i)->actionCount > 1)
			ss << game->GetHand()->GetCardAtIndex(i)->actions[1];
		else
			ss << " ";
		cout << ss.str();
		ss.str("");
	}
	cout << "|" << endl;
	//Print horizontal divider
	for (int i = 0; i < HAND_SIZE; i++) {
		cout << '+';
		cout << setfill('=') << setw(CARD_WIDTH - 1) << "=";
	}
	cout << "+" << setfill(' ') << endl;
}

