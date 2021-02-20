//============================================================================
// Name        : Player.h
// Author      : Amir Hossein Hadinezhad
// Version     : First Assainment
// Description : Player class implented code needed for biding part constrc , Player_Name,coin,bid,ID and their setters and getters , paymentCheck, Treasuary_Report, payCoin
//============================================================================
#pragma once
#include<iostream>

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
	void setBid(int* bidval);
	//getters
	int getCoin();
	std::string getPlayer_Name();
	int getID();
	int getBid();

	
	bool paymentCheck(int* payment);
	void Treasuary_Report();
	void payCoin(int* payment);





private:
	std::string player_Name;
	int coin;
	int bid;
	int ID;
};
