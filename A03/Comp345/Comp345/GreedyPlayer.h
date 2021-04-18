#pragma once
#include "Strategy.h"


class GreedyPlayer : public Strategy {
public:
	void SelectCard();
	int PlaceNewArmies();
	vector<int> MoveArmies(int numOfMoves);
	int BuildCity();
	vector<int> DestroyArmy();
	int AndOrAction();
};

