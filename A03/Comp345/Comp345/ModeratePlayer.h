#pragma once
#include "Strategy.h"


class ModeratePlayer : public Strategy {
public:
	void SelectCard();
	int PlaceNewArmies();
	vector<int> MoveArmies(int numOfMoves);
	int BuildCity();
	vector<int> DestroyArmy();
	int AndOrAction();
};

