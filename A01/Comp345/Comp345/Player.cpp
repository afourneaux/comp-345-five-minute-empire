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
/////////////////////////////Moved to Nested BiddingF///////////////////////////////////
//void Player::setBid(int* bidval)
//{
//	
//	if (paymentCheck(bidval))
//	{
//		bid = *bidval;
//	}
//}

void Player::setCoin(int val)
{
	coin = val;
}

void Player::setID(int id)
{
	ID = id;
}

/// <summary>
/// //////////////////////////////////////////// name of the Function
/// </summary>
/// <returns></returns>
std::string Player::getPlayer_Name()
{
	return player_Name;
}

int Player::getCoin()
{
	return coin;
}

/////////////////////////////Moved to Nested BiddingF///////////////////////////////////
//int Player::getBid()
//{
//	return bid;
//}

int Player::getID()
{
	return ID;
}
///////////////////////////////////////Please Use This Function I need It For Bidding and i guess its Nice to have
void Player::Treasuary_Report()
{
	std::cout << "Treasury report  :  You Have " << getCoin() << "coin" << std::endl;
}

/// <summary>
///////////////////////////////////////////////////////Its Payment Check If you want Add it ,, making sure they dont pay more that wahat they have
/// </summary>
/// <param name="payment"></param>
/// <returns></returns>
bool Player::paymentCheck(int* payment )
{
	int payagain = *payment;
	if (getCoin() < *payment)
	{
		std::cout << "You cant pay more that what you own" << std::endl;
		Treasuary_Report();
		std::cout << "Try Agin  ";
		//int payagain;
		std::cin >> *payment;

		paymentCheck(payment);

	}
	else
	{
		return true;
	}
	
}
/// <summary>
/// ////////////////////////////////////// im currently using this one for bidding //// things to note : takes pointer  , use Payment Check And threaseury_ Report ,, print some INFO
/// </summary>
/// <param name="payment"></param>
void Player::payCoin(int* payment)
{
	if (paymentCheck(payment))
	{
		std::cout << "Congratulation " << getPlayer_Name() <<"!" << std::endl;
		std::cout << "You successfully paied " << *payment << "coin" << std::endl;
		int remained = getCoin() - *payment;
		setCoin(remained);
		Treasuary_Report();

	}
}

