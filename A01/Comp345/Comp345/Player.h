//============================================================================
// Name        : Player.h
// Author      : Amir Hossein Hadinezhad
// Version     : First Assainment
// Description : Player class implented code needed for biding part constrc , Player_Name,coin,bid,ID and their setters and getters , paymentCheck, Treasuary_Report, payCoin
//============================================================================
#pragma once
#include<iostream>
#include "BiddingF.h"
/// <summary>
/// //////////////////////////////////  PLEASE PAY attention to THe name of the following as they are being used in bidding 
/// ?////////////////////////////////   getPlayer_Name   Treasuary_Report  getCoin  payCoin 
/// /////////////////////////////////   to create Player OBJ i also used   : setCoin   setPlayer_Name
/// </summary>
class Player
{
public:
	//getters
	Player();
	Player(std::string name, int initCoin);
	//setters
	void setPlayer_Name(std::string name);
	void setCoin(int value);
	void setID(int id);

/** ******************** */ //Moved to nested Class BiddingF
	//void setBid(int* bidval);
	//getters
///////////////////////////
	int getCoin();
	std::string getPlayer_Name();
	int getID();
	//int getBid();

	
	bool paymentCheck(int* payment);
	void Treasuary_Report();
	void payCoin(int* payment);
	/// <summary>
	/// Nested class Taking Care of Bidding//////////  our nsted Class  Its PUBLIC
	/// </summary>
	class BiddingF bf {};





private:
	std::string player_Name;
	int coin;
///***********/Moved to BiddingF class************************
/// 	int bid;
	int ID;
	
};
