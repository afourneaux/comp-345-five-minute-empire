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

int testBiddingFacility()
{
	string lastName = "";
	//Instantiating Test Players
	Player* table = new Player[NUM_OF_PLAYERS];

	//Getting lastname of players
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

	cout << "Testing Bidding Facility Stream insertion" << endl;
	BiddingFacility* bf = table[0].getBf();
	cout << *bf;
	cout << "Testing Bidding Facility Copy constructor" << endl;
	BiddingFacility* bf2 = new BiddingFacility(bf);
	delete bf;
	cout << *bf2;
	cout << "Testing Bidding Facility Assignment operator" << endl;
	BiddingFacility* bf3 = new BiddingFacility();
	*bf3 = *bf2; 
	delete bf2;
	cout << *bf3;
	delete bf3;


	return 0;
}


