//============================================================================
// Name        : Biding.cpp
// Author      : Amir Hossein Hadinezhad
// Version     : First Assainment
// Copyright   : Your copyright notice
// Description : biding part to initiate the game
//============================================================================
#include<iostream>
#include <vector>
#include "BiddingFacility.h"
#include <conio.h>
using namespace std;




int AskForBid(Player* player)
{
	int out;
	int val;   // STAND FOR "value" :)
	int max = player->getCoins();
	char bid[5];
	char c;
	//string value;
	int counter = 0;  // counter
	bool toInf = true;
	// do untill get the right result
	cout << player->getLastName() << ", please input your bid (ex: 1 -> 01)";
	while (toInf)
	{
		bid[counter] = _getch();
		c = bid[counter];
		// 2 digit format checking 
		if (counter > 2 && counter != 13)
		{

			cout << endl << "in order to be Private  only two digits format will be accepted , for exp : 01 for 1  " << endl << endl << "Try Again " << endl;
			counter = 0;
			bid[0] = 0;
			bid[1] = 0;
			bid[2] = 0;
			out = AskForBid(player);
			break;
		}
		counter++;
		// ASCII for Enter
		if (c == 13)
		{
			// 2 digit format checking
			cout << endl;
			if (counter == 2)
			{
				counter = 0;
				bid[0] = 0;
				bid[1] = 0;
				bid[2] = 0;
				cout << endl << "in order to be Private  only two digits format will be accepted , for exp : 01 for 1 " << endl << endl << "Try Again " << endl;
				out = AskForBid(player);
				break;
			}
			// save user input to "val"
			val = (bid[0] - 48) * 10 + (bid[1] - 48);  // char to int with ASCII calculation
			if (val > max)
			{
				counter = 0;
				bid[0] = 0;
				bid[1] = 0;
				bid[2] = 0;
				cout << endl << "Attention to your Treasuary" << endl;
				cout << player->getLastName() << " currently has " << player->getCoins() << " coins." << endl;

				cout << endl << "Try Again " << endl;
				out = AskForBid(player);
				break;
			}
			//when our bid val is in right format and amount
			else
			{
				out = val;
				toInf = false;
				//return bid value
				return out;
				break;
			}

		}
		else
		{
			// print * instead to keep it private
			cout << "*";
		}
	}
}
void CheckBidWinner(Player* players)
{
	cout << endl;
	cout << "  __________________________________________________________" << endl;
	cout << endl;
	int winner_Index = 0;
	int winner_bid = -1;
	for (int i = 0; i < NUM_OF_PLAYERS; i++)
	{
		//Print everyones name and their bid value
		cout << "             *================================*" << endl;
		cout << "		" << players[i].getLastName() << " : " << endl;
		cout << "		Bid :   " << players[i].getBf()->GetBid() << endl;
		cout << "             ===============================" << endl << endl;

		//find the highest bid
		if (players[i].getBf()->GetBid() > winner_bid)
		{
			winner_Index = i;
			winner_bid = players[i].getBf()->GetBid();
		}
		//if bid are equal compare names
		if (players[i].getBf()->GetBid() == winner_bid)
		{
			if (players[i].getLastName().compare(players[winner_Index].getLastName()) < 0)
			{
				winner_Index = i;
				winner_bid = players[i].getBf()->GetBid();
			}
		}
	}
	cout << endl;
	cout << endl;
	cout << "		********************************" << endl;
	cout << "		        ****************" << endl;
	cout << "		            ********" << endl;
	cout << endl;
	cout << "		         " << players[winner_Index].getLastName() << " won the bid " << endl;
	cout << "		            Bid :   " << players[winner_Index].getBf()->GetBid() << endl;
	cout << endl;
	int b = players[winner_Index].getBf()->GetBid();
	players[winner_Index].PayCoin(b);
	cout << endl;
	cout << "		            ********" << endl;
	cout << "		        ****************" << endl;
	cout << "		********************************" << endl;
	cout << endl;
	cout << endl;

}

BiddingFacility::BiddingFacility() {
	this->bid = 0;
}

BiddingFacility::BiddingFacility(BiddingFacility* bf) {
	this->bid = bf->bid;
}

BiddingFacility& BiddingFacility::operator=(const BiddingFacility& bf)
{
	//Check for self-assignment
	if (this == &bf) {
		return *this;
	}
	this->bid = bf.bid;
	return *this;
}

std::ostream& operator<<(std::ostream& out, const BiddingFacility& bf)
{
	out << "Bidding Facility: bid value " << bf.bid << endl;
	return out;
}
