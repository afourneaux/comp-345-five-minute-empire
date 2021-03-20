//============================================================================
// Name        : Biding.h
// Author      : Amir Hossein Hadinezhad
// Version     : First Assainment
// Copyright   : Your copyright notice
// Description : biding part to initiate the game
//============================================================================
#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
using namespace std;


struct Player;

class BiddingFacility{
public:
	int GetBid() { return bid; };
	void SetBid(int bidding) { bid = bidding; };
	BiddingFacility();
	BiddingFacility(BiddingFacility* bf);
	BiddingFacility& operator= (const BiddingFacility& bf);				// Assignment operator
	friend std::ostream& operator<< (std::ostream& out, const BiddingFacility& bf); // Stream insertion operator

private:
	int bid;
};

int AskForBid (Player *player);
int CheckBidWinner(Player* table , int const numPlayer);
int TestBiddingFacility();


