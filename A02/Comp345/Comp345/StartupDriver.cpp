#include <iostream>
#include "Player.h"
#include "Cards.h"
#include "Map.h"

static int Bank = 100;
const int GAME_TURNS_2_PLAYERS = 11;
const int GAME_TURNS_3_PLAYERS = 10;
const int GAME_TURNS_4_PLAYERS = 8;

const int STARTING_COINS_2_PLAYERS = 12;
const int STARTING_COINS_3_PLAYERS = 11;
const int STARTING_COINS_4_PLAYERS = 9;

int doBidding(Player* players_In_Game , int numPlayer )
{

	for (int i = 0; i < numPlayer; i++) {
		players_In_Game[i].setLastName("defaultPlayer" + to_string(i + 1));
		Bank -= 14;
		cout << "Player " << players_In_Game[i].GetLastName() << " has Joined" << endl;
		cout << "\n Bank : " << Bank << endl << endl << endl;

	}

	// set up the Bidding
	cout << endl << "Players for this game are: " << endl;
	for (int j = 0; j < numPlayer; j++) {
		cout << j + 1 << ". " << players_In_Game[j].GetLastName() << endl;
	}
	cout << endl;
	cout << endl << "__________________________________________________________________________________";
	cout << "\n Each Player has 14 coins \n Players have to place their bidd; The winner will will pay its bid amout and start the game and have to pay " << endl;
	for (int i = 0; i < numPlayer; i++)
	{
		cout << "___________________________________________________\n";
		players_In_Game[i].GetBf()->SetBid(AskForBid(&players_In_Game[i]));
		cout << "Your Bid has been submitted" << endl << endl;
	}
	int Player_Starter;
	//Winmer Index
	Player_Starter = CheckBidWinner(players_In_Game, numPlayer);
	Bank += players_In_Game[Player_Starter].GetBf()->GetBid();
	cout << "\n Bank : " << Bank << endl;
	return Player_Starter;
}
void initial_Player_setup(const int starterIndex ,Player* players_In_Game, int numAcctualPayer,   Player* Nutreal_Player, int numNutrealPlayer     ,Map* map, int numTerritory)
{
	//Territory* testLocation;
	int index = starterIndex;
	for (size_t i = 0; i < numAcctualPayer; i++)
	{
		int a = (index + i) % numAcctualPayer;
		cout << endl << players_In_Game[a].GetLastName() << " placed 4 arrmies on the origin" << endl;
			Territory * testLocation = map->GetTerritory(0);
			players_In_Game[a].PlaceNewArmies(testLocation);
			players_In_Game[a].PlaceNewArmies(testLocation);
			players_In_Game[a].PlaceNewArmies(testLocation);
			players_In_Game[a].PlaceNewArmies(testLocation);
	}
	cout << endl << Nutreal_Player[0].GetLastName() << " placed 4 arrmies on the origin" << endl;
	Territory* testLocation = map->GetTerritory(0);
	Nutreal_Player[0].PlaceNewArmies(testLocation);
	Nutreal_Player[0].PlaceNewArmies(testLocation);
	Nutreal_Player[0].PlaceNewArmies(testLocation);
	Nutreal_Player[0].PlaceNewArmies(testLocation);
	cout << endl << Nutreal_Player[0].GetLastName() << " placed 4 arrmies on the origin" << endl;
	index = starterIndex;
	int count=1;
	while (count <= 10)
	{
		cout << "\n*************************  Round " << count<<"  *************************";
		
		for (size_t i = 0; i < numAcctualPayer; i++)
		{
			int a = (index + i) % numAcctualPayer;
			cout << endl << "*_________________________";
			cout << endl << players_In_Game[a].GetLastName() << " Where do you want to place your Army? ";
			int armyLocarion;
			do
			{
				cout << endl << " select between 0 and" << (numTerritory - 1) <<"  :  ";
				cin >> armyLocarion;
			} while (armyLocarion<0 || armyLocarion >= numTerritory);
			Territory* testLocation = map->GetTerritory(armyLocarion);
			players_In_Game[a].PlaceNewArmies(testLocation);

		}
		count++;

	}
	///////////////////////Addd



}

int StartupMain() {
	cout << " Welcome to The Game " << endl;
	cout << "Press Enter to start!";
	cin.ignore(INT_MAX, '\n');

	
	cout << "\n For this assignment supposed to be \"2\" since there arennt any rules given for other numbers of players, most functions will still work anyways " << endl;
	cout << "How many players ?" << endl;
	int numOfPlayers;
	cin >> numOfPlayers;
	//deck will be created and shfell will be used -> implimentatinon added in card class
	Deck* deck = new Deck(numOfPlayers);
	Hand* hand = new Hand(deck);

	Player* players_In_Game = new Player[numOfPlayers];
	Player* Nutreal_Player = new Player();
	Nutreal_Player[0].setLastName("Nutreal_Player");
	cout << "\nThere are " << Bank << " Coins in The Bank For This Game \n";

	int starter_index = doBidding(players_In_Game, numOfPlayers);

	//Arbitary Map to test 
	int* arr = new int[4];
	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 1;
	arr[3] = 0;
	Map* map = new Map(arr, 4, numOfPlayers, 2);
	map->AddEdge(0, 1);
	map->AddEdge(0, 2);
	map->AddEdge(0, 3);
	map->AddEdge(1, 3);
	map->AddEdge(1, 2);
	map->AddEdge(2, 3);
	delete  arr;

	initial_Player_setup(starter_index, players_In_Game, numOfPlayers, Nutreal_Player, 1, map, 4);
	

	int gameTurns;
	if (numOfPlayers == 2) {
		gameTurns = GAME_TURNS_2_PLAYERS;
	}
	if (numOfPlayers == 3) {
		gameTurns = GAME_TURNS_3_PLAYERS;
	}
	if (numOfPlayers == 4) {
		gameTurns = GAME_TURNS_4_PLAYERS;
	}

	// DEBUG:
	gameTurns = 1;
	cout << endl << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<< endl;
	cout  << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout  << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "\nTest only the first round to see the cards , hand and their value\n";

	cout << "The number of Coins in the Bank of the game : " << Bank << endl << endl;
	cout << *hand;

	cout << "You have " << players_In_Game[starter_index].getCoins() << " coins." << endl;
	cout << "Please select a card to draw:" << endl;
	for (int handIndex = 0; handIndex < HAND_SIZE; handIndex++) {
		Card* cardAtIndex = hand->GetCardAtIndex(handIndex);
		cout << handIndex << ". \"" << cardAtIndex->name << "\" (" << hand->GetCostAtIndex(handIndex) << " coins)" << endl;
	}

	int desiredCardIndex;
	bool validCardIndex = false;

	// Select a card from the hand
	while (validCardIndex == false)
	{
		cin >> desiredCardIndex;
		if (cin.fail() || desiredCardIndex < 0 || desiredCardIndex >= HAND_SIZE) {
			cout << "Please enter a number from 0 to " << HAND_SIZE - 1 << endl;
			// Clear the CIN buffer
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else {
			// Card index is valid, check if the player can afford this card
			if (players_In_Game[starter_index].getCoins() < hand->GetCostAtIndex(desiredCardIndex)) {
				cout << "You cannot afford this card. You have " << players_In_Game[starter_index].getCoins() << " coins." << endl;
			}
			else {
				validCardIndex = true;
			}
		}
	}

	// Pay for the card
	players_In_Game[starter_index].PayCoin(hand->GetCostAtIndex(desiredCardIndex));
	Card* card = hand->Exchange(desiredCardIndex);
	Bank += hand->GetCostAtIndex(desiredCardIndex);
	cout << "\n Bank : " << Bank << endl;



	return 0;
}
