#pragma once
#include "Strategy.h"


class GreedyPlayer : public Strategy {
public:
	int PlaceNewArmies();
	int MoveArmies(int numOfMoves);
	int BuildCity();
	int DestroyArmy();
	int AndOrAction();
};

