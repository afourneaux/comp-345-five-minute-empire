#pragma once
#include<iostream>
#include <algorithm>
#include "Strategy.h"


class HumanPlayer : public Strategy {
public:
	int PlaceNewArmies();
	int MoveArmies(int numOfMoves);
	int BuildCity();
	int DestroyArmy();
	int AndOrAction();
};

