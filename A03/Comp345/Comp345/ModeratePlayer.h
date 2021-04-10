#pragma once
#include "Strategy.h"


class ModeratePlayer : public Strategy {
public:
	int PlaceNewArmies();
	int MoveArmies(int numOfMoves);
	int BuildCity();
	int DestroyArmy();
	int AndOrAction();
};

