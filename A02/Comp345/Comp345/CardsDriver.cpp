#include "Cards.h"
#include <iostream>

using namespace std;

int TestCards() {
	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
	cout << "TESTING CARDS CLASS" << endl;
	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
	Deck* deck = new Deck(2);
	Hand* hand = new Hand(deck);
	cout << "*******PRINTING DECK CONTENTS*******" << endl;
	cout << *deck;

	cout << endl;

	cout << "*******PRINTING HAND CONTENTS*******" << endl;
	cout << *hand;

	cout << endl;

	cout << "Drawing a card..." << endl;
	Card* card = deck->Draw();
	cout << "Card drawn:" << endl;
	cout << *card;

	cout << endl;

	cout << "Copying deck..." << endl;
	Deck* secondDeck = new Deck(deck);
	delete deck;
	cout << "*******PRINTING DECK CONTENTS*******" << endl;
	cout << *secondDeck;

	cout << endl;

	cout << "Copying hand..." << endl;
	Hand* secondHand = new Hand(hand);
	delete hand;
	cout << "*******PRINTING HAND CONTENTS*******" << endl;
	cout << *secondHand;

	delete secondDeck;
	delete secondHand;

	return 0;
}