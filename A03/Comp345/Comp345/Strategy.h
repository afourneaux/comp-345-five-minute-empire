#pragma once
#include "Game.h"

Player* player;
struct Player;

struct Strategy
{
public:
	virtual int PlaceNewArmies() = 0;
	virtual int MoveArmies(int numOfMoves) = 0;
	virtual int BuildCity() = 0;
	virtual int DestroyArmy() = 0;
	virtual int AndOrAction() = 0;
	Player* GetPlayer() { return player; };
private:
	Player* player;
};

