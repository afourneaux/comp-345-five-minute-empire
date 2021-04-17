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
	int maxLength = max(game->maxPlayerNameLength + 5, 16);
	cout << setiosflags(ios::left);

	//////////////////////////////////////////////////
	// PART 1: RENDER Game Statistics
	//////////////////////////////////////////////////
	cout << '+' << setfill('=') << setw(maxLength-1) << "=";
	cout << '+' << setfill(' ') << endl;
	cout << setw(maxLength) << "| PLAYER STATS";
	cout << '|';
	cout << " Special bonuses are displayed in ";
	SetConsoleTextAttribute(hConsole, 10); // Set colour to green 
	cout << "green" << endl;
	SetConsoleTextAttribute(hConsole, 15); // Set colour to  white
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
		if (game->currentPlayer == i) {
			SetConsoleTextAttribute(hConsole, 14);
			cout << '|' << right << setw(maxLength - 1) << ("-> " + game->players[i]->GetLastName() + " ");
			SetConsoleTextAttribute(hConsole, 15);
		}
		else
			cout << '|' << right << setw(maxLength - 1) << (game->players[i]->GetLastName() + " ");
		if (game->players[i]->getBonusForCoins()) {
			cout << left << "| ";
			SetConsoleTextAttribute(hConsole, 10); // Set colour to green if player gets bonus VP for coins
			cout << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getCoins();
			SetConsoleTextAttribute(hConsole, 15); // reset to White
		}
		else {
			cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getCoins();
		}
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

		if (game->players[i]->getBonusForFlying()) {
			cout << left << "| ";
			SetConsoleTextAttribute(hConsole, 10); // Set colour to green if player gets bonus VP for flying
			cout << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getBonusFlying();
			SetConsoleTextAttribute(hConsole, 15); // reset to White
		}
		else {
			cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getBonusFlying();
		}
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
	// PART 2: RENDER TRACKED CARD COUNTS BY PLAYER
	//////////////////////////////////////////////////
	cout << '+' << setfill('=') << setw(maxLength - 1) << "=";
	cout << '+' << setfill(' ') << endl;
	cout << setw(maxLength) << "| PLAYER CARDS";
	cout << '|' << endl;
	//Print horizontal divider
	cout << '+' << setfill('=') << setw(maxLength - 1) << "=";
	for (int i = 0; i < TRACKED_CARD_COUNT; i++) {
		cout << '+';
		cout << setfill('=') << setw(STATS_COLUMN_WIDTH - 1) << "=";
	}
	cout << "+" << setfill(' ') << endl;
	//Print headers
	cout << left << setw(maxLength) << "| Player";
	for (int i = 0; i < TRACKED_CARD_COUNT; i++) {
		cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << TRACKED_CARD_NAMES[i];
	}
	cout << left << "|" << endl;
	//Print horizontal divider
	cout << '+' << setfill('=') << setw(maxLength - 1) << "=";
	for (int i = 0; i < TRACKED_CARD_COUNT; i++) {
		cout << '+';
		cout << setfill('=') << setw(STATS_COLUMN_WIDTH - 1) << "=";
	}
	cout << "+" << setfill(' ') << endl;

	//Print player rows: player name + card count by type
	for (int i = 0; i < game->players.size(); i++) {
		if (game->currentPlayer == i) {
			SetConsoleTextAttribute(hConsole, 14);
			cout << '|' << right << setw(maxLength - 1) << ("-> " + game->players[i]->GetLastName() + " ");
			SetConsoleTextAttribute(hConsole, 15);
		}
		else
			cout << '|' << right << setw(maxLength - 1) << (game->players[i]->GetLastName() + " ");
		for (int j = 0; j < TRACKED_CARD_COUNT; j++) {
			if (game->players[i]->bonusForTrackedName[j]) {
				cout << left << "| ";
				SetConsoleTextAttribute(hConsole, 10); // Set colour to green if player gets bonus VP for the card type
				cout<< setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->cardsByTrackedName[j];
				SetConsoleTextAttribute(hConsole, 15); // reset to white
			}
			else {
				cout << left << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->cardsByTrackedName[j];
			}
		}
		cout << "|" << endl;
	}
	//Print horizontal divider
	cout << '+' << setfill('=') << setw(maxLength - 1) << "=";
	for (int i = 0; i < TRACKED_CARD_COUNT; i++) {
		cout << '+';
		cout << setfill('=') << setw(STATS_COLUMN_WIDTH - 1) << "=";
	}
	cout << "+" << setfill(' ') << endl;

	//////////////////////////////////////////////////
	// PART 3: RENDER MAP
	//////////////////////////////////////////////////
	cout << '+' << setfill('=') << setw(maxLength-1) << "=";
	cout << '+' << setfill(' ') << endl;
	cout << setw(maxLength) << "| MAP";
	cout << '|' << endl;
	//Print horizontal divider
	cout << '+' << setfill('=') << setw(maxLength-1) << "=";
	for (int i = 0; i < game->map->territory_count; i++) {
		cout << '+';
		cout << setfill('=') << setw(max(MAP_COLUMN_WIDTH - 1, game->map->territories[i].edgeStrLength + 3)) << "=";
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
		cout << left << setw(max(MAP_COLUMN_WIDTH - 2, game->map->territories[i].edgeStrLength + 2)) << terr;
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
			//if (connections_str_length > MAP_COLUMN_WIDTH - 2) break;

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
		cout << setfill('=') << setw(max(MAP_COLUMN_WIDTH - 1, game->map->territories[i].edgeStrLength + 3)) << "=";
	}
	cout << '+' << setfill(' ') << endl;

	//Print player rows: player name + city/army count per territory
	for (int i = 0; i < MasterGame->players.size(); i++) {
		if (game->currentPlayer == i) {
			SetConsoleTextAttribute(hConsole, 14);
			cout << '|' << right << setw(maxLength - 1) << ("-> " + game->players[i]->GetLastName() + " ");
			SetConsoleTextAttribute(hConsole, 15);
		}
		else
			cout << '|' << right << setw(maxLength - 1) << (game->players[i]->GetLastName() + " ");
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
			if (game->map->territories[j].army_count[i] > 6) {
				barGraph.append("Ax" + to_string(game->map->territories[j].army_count[i]));
			}
			else {
				for (int k = 0; k < game->map->territories[j].army_count[i]; k++)
					barGraph.append("A");
			}
			
			cout << left << setw(max(MAP_COLUMN_WIDTH - 2, game->map->territories[j].edgeStrLength + 2)) << barGraph;
			SetConsoleTextAttribute(hConsole, 15); // Reset console colour
		}
		cout << '|' << endl;
	}

	//Print horizontal divider
	cout << '+' << setfill('=') << setw(maxLength-1) << "=";
	for (int i = 0; i < game->map->territory_count; i++) {
		cout << '+';
		cout << setfill('=') << setw(max(MAP_COLUMN_WIDTH - 1, game->map->territories[i].edgeStrLength + 3)) << "=";
	}
	cout << '+' << setfill(' ') << endl;

	//////////////////////////////////////////////////
	// PART 4A: PRINT WINNER IF GAME IS OVER
	//////////////////////////////////////////////////
	if (game->gameOver) {
		cout << "===============================" << endl << endl;;
		cout << "The game is over!" << endl << endl;
		if (game->winnerIndex == -1) {
			cout << "It's a tie!" << endl;
		}
		else {
			cout << "The winner is... " << game->players[game->winnerIndex]->GetLastName() << "!" << endl;
		}
		cout << endl;
		cout << "===============================" << endl;
	}
	//////////////////////////////////////////////////
	// PART 4B: RENDER DRAFTABLE CARDS 
	//////////////////////////////////////////////////
	else {
	
		int handSize = game->GetHand()->GetSize();
		cout << '+' << setfill('=') << setw(CARD_WIDTH - 1) << "=";
		cout << '+' << setfill(' ') << endl;
		cout << '|' << setw(CARD_WIDTH - 1) << " AVAILABLE CARDS";
		cout << '|' << endl;

		//Print horizontal divider
		for (int i = 0; i < handSize; i++) {
			cout << '+';
			cout << setfill('=') << setw(CARD_WIDTH - 1) << "=";
		}
		cout << "+" << setfill(' ') << endl;
		//Print card index and cost
		for (int i = 0; i < handSize; i++) {
			cout << left << setw(5) << ("| [" + to_string(i) + "]");
			cout << right << setw(CARD_WIDTH - 5) << ("Cost: " + to_string(game->GetHand()->GetCostAtIndex(i)) + " ");
		}
		cout << "|" << endl;
		//Print card name
		for (int i = 0; i < handSize; i++) {
			cout << left << setw(CARD_WIDTH) << "| " + game->GetHand()->GetCardAtIndex(i)->name;
		}
		cout << "|" << endl;
		//Print horizontal divider
		for (int i = 0; i < handSize; i++) {
			cout << '+';
			cout << setfill('=') << setw(CARD_WIDTH - 1) << "=";
		}
		cout << "+" << setfill(' ') << endl;

		stringstream ss;
		//Print card abilities
		for (int i = 0; i < handSize; i++) {
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
		for (int i = 0; i < handSize; i++) {
			cout << "| " << left << setw(CARD_WIDTH - 2);
			ss << game->GetHand()->GetCardAtIndex(i)->actions[0];
			cout << ss.str();
			ss.str("");
		}

		cout << "|" << endl;
		//Print card and/or modifier if applicable
		for (int i = 0; i < handSize; i++) {
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
		for (int i = 0; i < handSize; i++) {
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
		for (int i = 0; i < handSize; i++) {
			cout << '+';
			cout << setfill('=') << setw(CARD_WIDTH - 1) << "=";
		}
		cout << "+" << setfill(' ') << endl;
	}
	
}

