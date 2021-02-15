//============================================================================
// Name        : Player.cpp
// Author      : Amir Hossein Hadinezhad
// Version     : First Assainment
// Description : Player class implented code needed for biding part constrc , Player_Name,coin,bid,ID and their setters and getters , paymentCheck, Treasuary_Report, payCoin
//============================================================================

#include <iostream>
#include "Player.h"


Player::Player() {

}
Player::Player(std::string name, int initCoin)
{
	player_Name = name;
	coin = initCoin;

}

void Player::setPlayer_Name(std::string name)
{
	player_Name = name;
}

void Player::setBid(int bidval)
{
	if (paymentCheck(bidval))
	{
		bid = bidval;
	}
}

void Player::setCoin(int val)
{
	coin = val;
}

void Player::setID(int id)
{
	ID = id;
}


std::string Player::getPlayer_Name()
{
	return player_Name;
}

int Player::getCoin()
{
	return coin;
}

int Player::getBid()
{
	return bid;
}

int Player::getID()
{
	return ID;
}

void Player::Treasuary_Report()
{
	std::cout << "Treasury report  :  You Have " << getCoin() << "coin" << std::endl;
}

bool Player::paymentCheck(int payment )
{
	if (getCoin() < payment)
	{
		std::cout << "You cant pay more that what you own" << std::endl;
		Treasuary_Report();
		std::cout << "Try Agin  ";
		int pay;
		std::cin >> pay;
		paymentCheck(pay);

	}
	else
	{
		return true;
	}
	
}

void Player::payCoin(int payment)
{
	if (paymentCheck(payment))
	{
		std::cout << "Congratulation " << getPlayer_Name() <<"!" << std::endl;
		std::cout << "You successfully paied " << payment << "coin" << std::endl;
		int remained = getCoin() - payment;
		setCoin(remained);
		Treasuary_Report();
	}
}

