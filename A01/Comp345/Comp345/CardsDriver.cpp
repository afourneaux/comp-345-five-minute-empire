#include "Cards.h"
#include <iostream>

using namespace std;

int testCards() {
	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
	cout << "TESTING CARDS CLASS" << endl;
	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
	Deck* deck = new Deck();
	Hand* hand = new Hand(deck);
	deck->Print();

	cout << endl;

	hand->Print();

	cout << endl;

	cout << "Drawing a card..." << endl;
	Card* card = deck->Draw();
	cout << "Card drawn:" << endl;
	card->Print();

	cout << endl;

	cout << "Copying deck..." << endl;
	Deck* secondDeck = new Deck(deck);
	delete deck;
	secondDeck->Print();

	cout << endl;

	cout << "Copying hand..." << endl;
	Hand* secondHand = new Hand(hand);
	delete hand;
	secondHand->Print();

	delete secondDeck;
	delete secondHand;

	return 0;
}