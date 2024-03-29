#include <iostream>
#include <algorithm>
#include <iomanip>
#include "GameObservers.h"
#include "Game.h"
#include <sstream>

using namespace std;

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

	ClearScreen();
	int maxLength = max(game->maxPlayerNameLength + 5, 16);
	cout << setiosflags(ios::left);

	//////////////////////////////////////////////////
	// PART 1: RENDER Game Statistics
	//////////////////////////////////////////////////
	cout << '+' << setfill('=') << setw(maxLength-1) << "=";
	cout << '+' << setfill(' ') << endl;
	cout << setw(maxLength) << "| PLAYER STATS";
	cout << '|';
	cout << " Special bonuses are indicated with *." << endl;
	//Print horizontal divider
	cout << '+' << setfill('=') << setw(maxLength-1) << "=";
	for (int i = 0; i < STATS_COLUMN_COUNT; i++) {
		cout << '+';
		cout << setfill('=') << setw(STATS_COLUMN_WIDTH - 1) << "=";
	}
	cout << "+" << setfill(' ') << endl;
	//Print headers
	cout << setw(maxLength) << "| Player";
	cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << "Coins";
	cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << "# Territories";
	cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << "# Continents";
	cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << "# Elixirs";
	cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << "Army Bonus";
	cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << "Move Bonus";
	cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << "Flying Bonus";
	cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << "Immune";
	cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << "Card VPs";
	cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << "Total VP";
	cout << "|" << endl;
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
			cout << '|' << right << setw(maxLength - 1) << ("-> " + game->players[i]->GetLastName() + " ");
		}
		else
			cout << '|' << right << setw(maxLength - 1) << (game->players[i]->GetLastName() + " ");
		cout << left;
		if (game->players[i]->GetBonusForCoins()) {
			cout << "| ";
			cout << setw(STATS_COLUMN_WIDTH - 2) << to_string(game->players[i]->GetCoins()) + "*";
		}
		else {
			cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->GetCoins();
		}
		cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getTerritoryScore();
		cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getContinentScore();
		if (game->players[i]->getElixirWinner()) {
			cout << "| ";
			cout << setw(STATS_COLUMN_WIDTH - 2) << to_string(game->players[i]->getElixirs()) + "*";
		}
		else {
			cout << "| ";
			cout << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getElixirs();
		}
		cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->GetBonusArmies();
		cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->GetBonusMoves();

		if (game->players[i]->GetBonusForFlying()) {
			cout << "| ";
			cout << setw(STATS_COLUMN_WIDTH - 2) << to_string(game->players[i]->GetBonusFlying()) + "*";
		}
		else {
			cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->GetBonusFlying();
		}
		cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->GetBonusImmune();
		cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getCardScore();
		cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->getTotalScore();

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
	cout << setw(maxLength) << "| Player";
	for (int i = 0; i < TRACKED_CARD_COUNT; i++) {
		cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << TRACKED_CARD_NAMES[i];
	}
	cout << "|" << endl;
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
			cout << '|' << right << setw(maxLength - 1) << ("-> " + game->players[i]->GetLastName() + " ");
		}
		else
			cout << '|' << right << setw(maxLength - 1) << (game->players[i]->GetLastName() + " ");
		cout << left;
		for (int j = 0; j < TRACKED_CARD_COUNT; j++) {
			if (game->players[i]->bonusForTrackedName[j]) {
				cout << "| ";
				cout<< setw(STATS_COLUMN_WIDTH - 2) << to_string(game->players[i]->cardsByTrackedName[j]) + "*";
			}
			else {
				cout << "| " << setw(STATS_COLUMN_WIDTH - 2) << game->players[i]->cardsByTrackedName[j];
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
	cout << setw(maxLength) << "|";
	for (int i = 0; i < game->map->territory_count; i++) {
		cout << "| ";
		string terr;
		if (game->map->starting_territory_index == i)
			terr = "S-T" + to_string(i) + ", C" + to_string(game->map->territories[i].continentID);
		else
			terr = "T" + to_string(i) + ", C" + to_string(game->map->territories[i].continentID);
		cout << setw(max(MAP_COLUMN_WIDTH - 2, game->map->territories[i].edgeStrLength + 2)) << terr;
	}
	cout << '|' << endl;

	//Print headers row 2: Player label + adjacent territories
	cout << setw(maxLength) << "| Player";
	for (int i = 0; i < game->map->territory_count; i++) {
		cout << "|->" ;
		int connections_str_length = 3;
		Edge* temp = game->map->territories[i].head;
		while (temp != nullptr) {
			string conn;
			if (temp->movement_cost == game->map->WATER_MOVEMENT_COST)
				conn = to_string(temp->destination_territory->territoryID) + "W ";
			else
				conn = to_string(temp->destination_territory->territoryID) + " ";
			cout << conn;
			connections_str_length += conn.length();
			temp = temp->next;
		}
		cout << setw(MAP_COLUMN_WIDTH - connections_str_length) << " ";
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
			cout << '|' << right << setw(maxLength - 1) << ("-> " + game->players[i]->GetLastName() + " ");
		}
		else
			cout << '|' << right << setw(maxLength - 1) << (game->players[i]->GetLastName() + " ");
		cout << left;
		for (int j = 0; j < game->map->territory_count; j++) {
			cout << "|";
			if (game->map->territories[j].controlling_player == i)
				cout << "*";
			else
				cout <<" ";
			string barGraph = "";
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
			
			cout << setw(max(MAP_COLUMN_WIDTH - 2, game->map->territories[j].edgeStrLength + 2)) << barGraph;
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
			cout << setw(5) << ("| [" + to_string(i) + "]");
			cout << right << setw(CARD_WIDTH - 5) << ("Cost: " + to_string(game->GetHand()->GetCostAtIndex(i)) + " ");
		}
		cout << left << "|" << endl;
		//Print card name
		for (int i = 0; i < handSize; i++) {
			cout << setw(CARD_WIDTH) << "| " + game->GetHand()->GetCardAtIndex(i)->name;
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
			cout << "| " << setw(CARD_WIDTH - 2);
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

void ClearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

PlayerStateView::PlayerStateView()
{
	game = nullptr;
}

PlayerStateView::PlayerStateView(Game* game)
{
	this->game = game;
}

PlayerStateView::~PlayerStateView()
{
}

void PlayerStateView::Update()
{
	Display();
}

void PlayerStateView::Display()
{
	// Clear currentplayer's actions vector at the end of their turn
	Player* currentPlayer;
	if (game->currentTurn != 0 && !game->gameOver) {
		currentPlayer = game->players[game->currentPlayer]; // current player
		cout << endl << "+========================================+" << endl;
		cout << "  ROUND #" << game->currentTurn << ": It's " << currentPlayer->GetLastName() << "'s turn" << endl;
		cout << "+========================================+" << endl;
		if (currentPlayer->GetHand().size() == game->currentTurn && currentPlayer->GetHand().size() != 0) {
			cout << "  - Selects '" << currentPlayer->GetHand()[game->currentTurn-1]->name << "' card" << endl;
			for (int i = 0; i < currentPlayer->actions.size(); i++) {
				cout << currentPlayer->actions[i] << endl;
			}
		}
		cout << "+========================================+\n" << endl;
	}
}