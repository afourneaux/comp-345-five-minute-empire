//============================================================================
// Name        : Biding.h
// Author      : Amir Hossein Hadinezhad
// Version     : First Assainment
// Copyright   : Your copyright notice
// Description : biding part to initiate the game
//============================================================================
#pragma once
#include<iostream>
#include<vector>
#include"Player.h"


	void welcome();
	/// <summary>
	/// how may players 
	/// </summary>
	/// <returns>vector corispond to the num of player in the game</returns>
	std::vector <Player> NumPlayer();
	std::vector <Player> askPlayersInfo(std::vector<Player> players_In_Game);
	/// <summary>
	/// Rec Func that ask and store bid val privately
	/// </summary>
	/// <param name="gamer"> a player in game</param>
	/// <returns>bid val of a gamer</returns>
	int privatelyAsk (Player gamer);
	void WhoStart(std::vector<Player> players_In_Game);
	void doBiding();

	int test_BiddingMain();

