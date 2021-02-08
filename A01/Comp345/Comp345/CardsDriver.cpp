#include "Cards.h"
#include <iostream>

using namespace std;

int testCards() {
	Deck* deck = new Deck();
	Hand* hand = new Hand(deck);
	deck->Print();
	hand->Print();

	return 0;
}