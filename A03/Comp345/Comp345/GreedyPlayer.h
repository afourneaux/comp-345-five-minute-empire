#pragma once
#include "Strategy.h"


class GreedyPlayer : public Strategy {
public:
	void SelectCard();
	int PlaceNewArmies();
	int MoveArmies(int numOfMoves);
	int BuildCity();
	int DestroyArmy();
	int AndOrAction();
};

