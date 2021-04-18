#pragma once
#include "Game.h"

struct Player;

struct Strategy
{
public:
	virtual void SelectCard() = 0;
	virtual int PlaceNewArmies() = 0;
	virtual vector<int> MoveArmies(int numOfMoves) = 0;
	virtual int BuildCity() = 0;
	virtual vector<int> DestroyArmy() = 0;
	virtual int AndOrAction() = 0;

	Player* GetPlayer() { return player; };
	void SetPlayer(Player* playa) { player = playa; };

private:
	Player* player;
};

