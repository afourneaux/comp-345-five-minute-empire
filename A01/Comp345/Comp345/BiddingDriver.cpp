//============================================================================
// Name        : BidingMAin.cpp
// Author      : Amir Hossein Hadinezhad
// Version     : First Assainment
// Copyright   : Your copyright notice
// Description : biding part to initiate the game
//============================================================================
#include<iostream>
#include <vector> 
#include "Player.h"
#include "BiddingFacility.h"

int TestBiddingFacility()
{
	string lastName = "";
	//Instantiating Test Players
	Player* table = new Player[NUM_OF_PLAYERS];

	//Getting last name of players
	for (int i = 0; i < NUM_OF_PLAYERS; i++) {
		cout << "Enter the name of Player " << i + 1 << ": ";
		cin >> lastName;
		table[i].setLastName(lastName);
	}
	cout << endl << "Players for this game are: " << endl;
	for (int j = 0; j < NUM_OF_PLAYERS; j++) {
		cout << j + 1 << ". " << table[j].getLastName() << endl;
	}
	cout << endl;

	for (int i = 0; i < NUM_OF_PLAYERS; i++)
		table[i].getBf()->SetBid(AskForBid(&table[i]));

	CheckBidWinner(table);

	return 0;
}


