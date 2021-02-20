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
	int ask(Player p);
	void WhoStart(std::vector<Player> players_In_Game);
	void doBiding();

