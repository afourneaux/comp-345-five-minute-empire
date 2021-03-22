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
#include "Game.h"

using namespace std;

struct Player;
class Game;

class BiddingFacility {
public:
	int GetBid() { return bid; };
	void SetBid(int bidding) { bid = bidding; };
	BiddingFacility();
	BiddingFacility(BiddingFacility* bf);
	BiddingFacility& operator= (const BiddingFacility& bf);				// Assignment operator
	friend std::ostream& operator<< (std::ostream& out, const BiddingFacility& bf); // Stream insertion operator
	static int DoBidding(vector<Player*> players, int playerCount);
private:
	int bid;
};

int AskForBid(Player* player);
int CheckBidWinner(vector<Player*> table, int const numPlayer);


