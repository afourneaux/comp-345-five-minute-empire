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

// Query the user for their bid, but do not display their input in the window
int AskForBid(Player* player)
{
	int out;
	int numericInput;
	char bid[5];
	char input;
	int counter = 0;
	cout << player->GetLastName() << ", please input a two-digit bid (example: input 03 instead of 3)" << endl;
	cout << "You Currently have 14 Coins to Bid";
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
}

// Compare each player's bid and determine a winner
int CheckBidWinner(Player* players)
{
	cout << endl;
	cout << "  __________________________________________________________" << endl;
	cout << endl;
	int winnerIndex = 0;
	int winnerBid = -1;
	for (int i = 0; i < NUM_OF_PLAYERS; i++)
	{
		// Print everyone's name and their bid value
		cout << "             *================================*" << endl;
		cout << "		" << players[i].GetLastName() << " : " << endl;
		cout << "		Bid :   " << players[i].GetBf()->GetBid() << endl;
		cout << "             ===============================" << endl << endl;

		// Find the highest bid
		if (players[i].GetBf()->GetBid() > winnerBid)
		{
			winnerIndex = i;
			winnerBid = players[i].GetBf()->GetBid();
		}
		// Break ties by last name
		if (players[i].GetBf()->GetBid() == winnerBid)
		{
			if (players[i].GetLastName().compare(players[winnerIndex].GetLastName()) < 0)
			{
				winnerIndex = i;
				winnerBid = players[i].GetBf()->GetBid();
			}
		}
	}
	cout << endl;
	cout << endl;
	cout << "		********************************" << endl;
	cout << "		        ****************" << endl;
	cout << "		            ********" << endl;
	cout << endl;
	cout << "		         " << players[winnerIndex].GetLastName() << " won the bid " << endl;
	cout << "		            Bid :   " << players[winnerIndex].GetBf()->GetBid() << endl;
	cout << endl;
	int winningBid = players[winnerIndex].GetBf()->GetBid();
	players[winnerIndex].PayCoin(winningBid);
	cout << endl;
	cout << "		            ********" << endl;
	cout << "		        ****************" << endl;
	cout << "		********************************" << endl;
	cout << endl;
	cout << endl;
	return winnerIndex;
}

/// <summary>
/// get Players data  
/// </summary>
/// <param name="players_In_Game"> ppl in the game</param>
/// <returns>vector of Players Obj with theit names , bid and coin</returns>
//std::vector <Player> askPlayersInfo(std::vector<Player> players_In_Game)
//{
//
//	for (int i = 0; i < NumOfPlayer; i++)
//	{
//		std::string name;
//		int pay;
//
//
//
//		std::cout << std::endl;
//		std::cout << "________________________________" << std::endl;
//		std::cout << "Player" << i << " :" << std::endl;
//		std::cout << "What is your name?  ";
//		std::cin >> name;
//		players_In_Game[i].setPlayer_Name(name);
//		players_In_Game[i].setCoin(10);
//		//Player newPlayer(name, 10);
//		std::cout << std::endl;
//		std::cout << "How much do you want to bid?  ";
//		//newPlayer.Treasuary_Report();
//		players_In_Game[i].Treasuary_Report();
//		std::cout << std::endl << "in order to be Private  only two digits format will be accepted , for exp : 01 for 1 " << std::endl << std::endl << std::endl;;
//		pay = ask(players_In_Game[i]);
//
//
//
//
//		//std::cin >> pay;
//
//		players_In_Game[i].setBid(&pay);
//		//players_In_Game.push_back(newPlayer);
//	}
//
//	return players_In_Game;
//}
/// <summary>
/// Print The witter
/// </summary>
/// <param name="players_In_Game"> players in the game</param>
//void WhoStart(std::vector<Player> players_In_Game)
//{
//	std::cout << std::endl;
//	std::cout << "  __________________________________________________________" << std::endl;
//	std::cout << std::endl;
//	int winner_Index = 0;
//	int winner_bid = -1;
//	for (int i = 0; i < NumOfPlayer; i++)
//	{
//		//Print everyones name and their bid value
//		std::cout << "             *================================*" << std::endl;
//		std::cout << "		" << players_In_Game[i].getPlayer_Name() << " : " << std::endl;
//		std::cout << "		Bid :   " << players_In_Game[i].getBid() << std::endl;
//		std::cout << "             ===============================" << std::endl << std::endl;
//
//		//find the highest bid
//		if (players_In_Game[i].getBid() > winner_bid)
//		{
//			winner_Index = i;
//			winner_bid = players_In_Game[i].getBid();
//		}
//		//if bid are equal compare names
//		if (players_In_Game[i].getBid() == winner_bid)
//		{
//			if (players_In_Game[i].getPlayer_Name().compare(players_In_Game.at(winner_Index).getPlayer_Name()) < 0)
//			{
//				winner_Index = i;
//				winner_bid = players_In_Game[i].getBid();
//
//			}
//
//		}
//
//	}

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
