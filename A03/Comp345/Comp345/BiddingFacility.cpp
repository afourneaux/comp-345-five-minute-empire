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
extern Game* MasterGame;

// Query the user for their bid, but do not display their input in the window
int AskForBid(Player* player)
{
	int out;
	int numericInput;
	char bid[5];
	char input;
	int counter = 0;
	cout << player->GetLastName() << ", please input a two-digit bid (example: input 03 instead of 3)" << endl;
	cout << "You Currently have "<< player->getCoins()<<" Coins to Bid. ";
	// Loop until a valid value is input
	while (true)
	{
		// Get the next key without displaying it
		input = _getch();
		bid[counter] = input;
		
		counter++;

		// 2 digit format checking
		if (counter > 2 && bid[counter-1] != 13)
		{
			cout << endl;

			cout << "Invalid format. please input a two-digit bid (example: input \"03\" instead of \"3\")" << endl;
			cout << endl;
			cout << "Try Again" << endl;
			counter = 0;
			bid[0] = 0;
			bid[1] = 0;
			bid[2] = 0;
			out = AskForBid(player);
			break;
		}
		

		
		// When the Enter key is detected
		if (input == 13)
		{
			// 2 digit format checking
			cout << endl;
			if (counter == 2)
			{
				counter = 0;
				bid[0] = 0;
				bid[1] = 0;
				bid[2] = 0;
				cout << endl;
				cout << "Invalid format. please input a two-digit bid (example: input \"03\" instead of \"3\")" << endl;
				cout << endl;
				cout << "Try Again" << endl;
				out = AskForBid(player);
				break;
			}
			// Save user input
			numericInput = (bid[0] - 48) * 10 + (bid[1] - 48);  // char to int with ASCII calculation
			if (numericInput > player->getCoins())
			{
				counter = 0;
				bid[0] = 0;
				bid[1] = 0;
				bid[2] = 0;
				cout << endl << "You do not have enough coins." << endl;
				cout << player->GetLastName() << " currently has " << player->getCoins() << " coins." << endl;

				cout << endl << "Try Again " << endl;
				out = AskForBid(player);
				break;
			}
			// User input is a valid format and value
			else
			{
				return numericInput;
			}
		}
		else
		{
			// Print * instead to keep it private
			cout << "*";
		}
	}

	return 0;
}

// Compare each player's bid and determine a winner
int CheckBidWinner(vector<Player*> players , int const numPlayer)
{
	cout << endl;
	cout << "  __________________________________________________________" << endl;
	cout << endl;
	int winnerIndex = 0;
	int winnerBid = -1;
	for (int i = 0; i < numPlayer; i++)
	{
		// Print everyone's name and their bid value
		cout << "             *================================*" << endl;
		cout << "		" << players[i]->GetLastName() << " : " << endl;
		cout << "		Bid :   " << players[i]->GetBf()->GetBid() << endl;
		cout << "             ===============================" << endl << endl;

		// Find the highest bid
		if (players[i]->GetBf()->GetBid() > winnerBid)
		{
			winnerIndex = i;
			winnerBid = players[i]->GetBf()->GetBid();
		}
		// Break ties by last name
		if (players[i]->GetBf()->GetBid() == winnerBid)
		{
			if (players[i]->GetLastName().compare(players[winnerIndex]->GetLastName()) < 0)
			{
				winnerIndex = i;
				winnerBid = players[i]->GetBf()->GetBid();
			}
		}
	}
	cout << endl;
	cout << endl;
	cout << "		********************************" << endl;
	cout << "		        ****************" << endl;
	cout << "		            ********" << endl;
	cout << endl;
	cout << "		         " << players[winnerIndex]->GetLastName() << " won the bid " << endl;
	cout << "		            Bid :   " << players[winnerIndex]->GetBf()->GetBid() << endl;
	cout << endl;
	int winningBid = players[winnerIndex]->GetBf()->GetBid();
	players[winnerIndex]->PayCoin(winningBid);
	cout << endl;
	cout << "		            ********" << endl;
	cout << "		        ****************" << endl;
	cout << "		********************************" << endl;
	cout << endl;
	cout << endl;
	return winnerIndex;
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

int BiddingFacility::DoBidding(vector<Player*> players, int playerCount)
{
	// set up the Bidding
	cout << endl << "Players for this game are: " << endl;
	for (int j = 0; j < playerCount; j++) {
		cout << j + 1 << ". " << players[j]->GetLastName() << endl;
	}
	cout << endl;
	cout << endl << "__________________________________________________________________________________";
	cout << "\n Each Player has " << players[0]->getCoins() << " coins \n Players have to place their bid. The winner will pay their bid amount and start the game and have to pay" << endl;
	for (int i = 0; i < playerCount; i++)
	{
		cout << "___________________________________________________\n";
		players[i]->GetBf()->SetBid(AskForBid(players.at(i)));
		cout << "Your bid has been submitted" << endl << endl;
	}
	int Player_Starter;
	//Winner Index
	Player_Starter = CheckBidWinner(players, playerCount);
	MasterGame->bank += players[Player_Starter]->GetBf()->GetBid();
	cout << "\nBank : " << MasterGame->bank << endl;
	return Player_Starter;
}