#pragma once
#include <iostream>
#include "Player.h"
#include "Map.h"
#include <vector>

const int ELIXIR_BONUS = 2;

void ComputeScore(Map* map, Player* players, int player_count);
void TestComputeScore();