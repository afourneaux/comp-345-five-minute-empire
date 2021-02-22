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

const int NUM_OF_PLAYERS = 2;

struct Player;

class BiddingFacility{
public:
	int GetBid() { return bid; };
	void SetBid(int bidding) { bid = bidding; };
private:
	int bid;
};

int AskForBid (Player *player);
void CheckBidWinner(Player* table);
int testBiddingFacility();


