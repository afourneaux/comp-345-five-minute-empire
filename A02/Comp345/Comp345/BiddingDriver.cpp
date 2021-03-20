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
	int playerNumber = 2;
	string lastName = "";
	//Instantiating Test Players
	Player* table = new Player[playerNumber];

	//Getting last name of players
	for (int i = 0; i < playerNumber; i++) {
		cout << "Enter the name of Player " << i + 1 << ": ";
		cin >> lastName;
		table[i].SetLastName(lastName);
	}
	cout << endl << "Players for this game are: " << endl;
	for (int j = 0; j < playerNumber; j++) {
		cout << j + 1 << ". " << table[j].GetLastName() << endl;
	}
	cout << endl;

	for (int i = 0; i < playerNumber; i++)
		table[i].GetBf()->SetBid(AskForBid(&table[i]));

	CheckBidWinner(table , playerNumber);

	cout << "Testing Bidding Facility Stream insertion" << endl;
	BiddingFacility* bf = table[0].GetBf();
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


