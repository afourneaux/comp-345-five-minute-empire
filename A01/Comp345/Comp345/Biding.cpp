//============================================================================
// Name        : Biding.cpp
// Author      : Amir Hossein Hadinezhad
// Version     : First Assainment
// Copyright   : Your copyright notice
// Description : biding part to initiate the game
//============================================================================
#include<iostream>
#include<string>
#include <vector>
#include "Player.h"
#include <stdio.h>
#include <conio.h>

int NumOfPlayer;

void welcome()
{
	std::cout << "	Hello" << std::endl << "Welcome to the game" << std::endl;
	std::cout << "We do the bid now , every palyer will get 10 coins hand if they win the bid they can start the game but they have t0 pay their bid!" << std::endl;
}
/// <summary>
/// How many Players /////////**************************** can be removed if you create PLayers some where else
/// </summary>
/// <returns> vecter of pplayers in the game</returns>
std::vector <Player> NumPlayer() {
	int  players;
	do
	{
		
		std::cout << "How Many players? Beetween 2 to 4?" << std::endl;
		std::cin >> players;

	} while (players > 4 || players < 2);

		NumOfPlayer = players;
		std::vector <Player> players_In_Game;
		players_In_Game.resize(players);
		std::cout << std::endl;
		return players_In_Game;

		//players_In_Game[1].setCoin(2);

}
//************************************************************


/// <summary>
/// Rec Func that get the ask and return bid val privately
/// </summary>
/// <param name="gamer"> a player in game</param>
/// <returns>bid val of a gamer</returns>
int privatelyAsk (Player gamer)
{
	int out;  
	int val;   // STAND FOR "value" :)
	int max = gamer.getCoin();
	char bid[5];
	char c;
	//std::string value;
	int counter = 0;  // counter
	bool toInf = true;
	// do untill get the right result
	while (toInf)
	{
		bid[counter] = _getch();
		c = bid[counter];
		// 2 digit format checking 
		if (counter>2 && counter!=13)
		{
			
			std::cout << std::endl << "in order to be Private  only two digits format will be accepted , for exp : 01 for 1  " << std::endl <<std::endl << "Try Again " << std::endl;
			counter = 0;
			bid[0]=0;
			bid[1]=0;
			bid[2]=0;
			out=privatelyAsk(gamer);
			break;
		}
		counter++;
		// ASCII for Enter
		if (c == 13)
		{
			// 2 digit format checking
			if (counter==2)
			{
				counter = 0;
				bid[0] = 0;
				bid[1] = 0;
				bid[2] = 0;
				std::cout << std::endl << "in order to be Private  only two digits format will be accepted , for exp : 01 for 1 " << std::endl << std::endl << "Try Again " << std::endl;
				out =privatelyAsk(gamer);
				break;
			}
			// save user input to "val"
			val= (bid[0]-48 )*10 +( bid[1]-48) ;  // char to int with ASCII calculation
			if (val>max)
			{
				counter = 0;
				bid[0] = 0;
				bid[1] = 0;
				bid[2] = 0;
				std::cout << std::endl << "Attention to your Treasuary" << std::endl;
				gamer.Treasuary_Report();
				
				std::cout << std::endl << "Try Again " << std::endl;
				out=privatelyAsk(gamer);
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
			std::cout << "*";
		}

	}

	return out;
	
}

/// <summary>
/// get Players data  
/// </summary>
/// <param name="players_In_Game"> ppl in the game</param>
/// <returns>vector of Players Obj with theit names , bid and coin</returns>
std::vector <Player> askPlayersInfo( std::vector<Player> players_In_Game)
{
	
	for (int i = 0; i < NumOfPlayer; i++)
	{
		std::string name;
		int pay;
		//////////////////*************************** in between can be removed if you create PLayers OBj some where else but PLEASE pass me VECTOR of player 
		

		std::cout << std::endl;
		std::cout << "________________________________" << std::endl;
		std::cout << "Player" << i << " :" << std::endl;
		std::cout << "What is your name?  ";
		std::cin >> name;
		players_In_Game[i].setPlayer_Name(name);
		players_In_Game[i].setCoin(10);
		//Player newPlayer(name, 10);
		std::cout << std::endl;
		
		/////////////////////***************************************************************************************
		/// 
		/// 
	
		std::cout << "How much do you want to bid?  ";
		//newPlayer.Treasuary_Report();
		players_In_Game[i].Treasuary_Report();
		std::cout << std::endl << "in order to be Private  only two digits format will be accepted , for exp : 01 for 1 " << std::endl << std::endl << std::endl;;
		pay = privatelyAsk(players_In_Game[i]);
	



		//std::cin >> pay;
		
		players_In_Game[i].bf.setBid( &pay);
		//players_In_Game.push_back(newPlayer);
	}

	return players_In_Game;
}
/// <summary>
/// Print The winner
/// </summary>
/// <param name="players_In_Game"> players in the game</param>
void WhoStart(std::vector<Player> players_In_Game)
{
	std::cout << std::endl;
	std::cout << "  __________________________________________________________" << std::endl;
	std::cout << std::endl;
	int winner_Index=0;
	int winner_bid=-1;
	for (int i = 0; i < NumOfPlayer; i++)
	{
		//Print everyones name and their bid value
		std::cout << "             *================================*" << std::endl;
		std::cout << "		"<< players_In_Game[i].getPlayer_Name() << " : " << std::endl;
		std::cout << "		Bid :   " <<players_In_Game[i].bf.getBid() << std::endl;
		std::cout << "             ===============================" << std::endl << std::endl;

		//find the highest bid
		if (players_In_Game[i].bf.getBid() > winner_bid)
		{
			winner_Index = i;
			winner_bid = players_In_Game[i].bf.getBid();
		}
		//if bid are equal compare names
		if (players_In_Game[i].bf.getBid() == winner_bid)
		{
			if (players_In_Game[i].getPlayer_Name().compare(players_In_Game.at(winner_Index).getPlayer_Name()) < 0 )
			{
				winner_Index = i;
				winner_bid = players_In_Game[i].bf.getBid();

			}

		}
		
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "		********************************" << std::endl;
	std::cout << "		        ****************" << std::endl;
	std::cout << "		            ********" << std::endl;
	std::cout << std::endl;
	std::cout << "		         "<< players_In_Game[winner_Index].getPlayer_Name() << " won the bid " << std::endl;
	std::cout << "		            Bid :   " << players_In_Game[winner_Index].bf.getBid() << std::endl;
	std::cout << std::endl;
	int b = players_In_Game[winner_Index].bf.getBid();
	int* p = &b;
	players_In_Game[winner_Index].payCoin(p);
	std::cout << std::endl;
	std::cout << "		            ********" << std::endl;
	std::cout << "		        ****************" << std::endl;
	std::cout << "		********************************" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

}
/// <summary>
/// do all bidding stuff
/// </summary>
void doBiding()
{
	welcome();
	/// <summary>
	/// //////////////////////////////////////////////////// modifivation will be needed if you create Player OBJ somewherre else 
	/// </summary>
	WhoStart (askPlayersInfo ( NumPlayer() ) );

}


