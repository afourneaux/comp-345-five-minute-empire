#pragma once
#include <string>

using namespace std;

const int DECK_SIZE = 11;	// The total number of implemented cards in the deck
const int HAND_SIZE = 6;	// The number of face-up cards in the hand

enum CardAction {
	eAction_None,
	eAction_PlaceArmies,
	eAction_MoveArmies,
	eAction_BuildCity,
	eAction_DestroyArmies
};

enum CardChoice {
	eChoice_None,
	eChoice_And,
	eChoice_Or
};

enum CardAbility {
	eAbility_None,
	eAbility_PlusOneMove,
	eAbility_PlusOneArmy,
	eAbility_Flying,
	eAbility_Elixir,
	eAbility_Coins,
	eAbility_VpPerCardName,
	eAbility_VpPerCoins
};

struct Action {
	CardAction action;			// The type of action allowed by the card
	int actionValue;			// The value associated to the card's action, for example "move *2* armies"
	string ToString();
};

struct Ability {
	CardAbility type;			// The type of ability granted by the card
	int value;					// The value associated to the ability
	string setName;				// If the card grants VP Per Card Set, what name does it target?
	int setTarget;				// If the card grants VP Per Card Set, how many cards does the holder need?
	bool countSetOnce;			// If true, VP for having a card set is only granted once
	string ToString();
};

struct Card {
	Card();						// Default constructor
	Card(Card* card);			// Copy constructor
	string name;				// Title of the card
	string image;				// Source file containing card art
	Action* actions;			// The set of action(s) granted by the card
	int actionCount;			// How many actions this card contains
	CardChoice actionChoice;	// If two actions exist, determine whether it is an AND or OR relationship
	Ability* abilities;			// The ability/abilities listed on the card
	int abilityCount;			// How many abilities are on the card
	void Print();				// Output the card's formatted data to cout
};

//TODO: assignment operator, stream insertion
class Deck {
public:
	Deck();
	Deck(Deck* deck);
	Card* Draw();				// Return and remove the first card from the deck
	void Print();				// Output the deck's contents to cout
private:
	void Generate();			// Populate the deck with hard-coded cards
	Card* cards;				// The contents of the deck
	int deckIndex;				// The current index representing the top of the deck
};

//TODO: assignment operator, stream insertion, Player interaction in Exchange
class Hand {
public:
	Hand(Deck* deck);								// Default constructor
	Hand(Hand* hand);								// Copy constructor
	//~Hand();										// Destructor
	Card* Exchange(int index/*, Player player*/);	// Spend coins to obtain a card 
	Card* GetCardAtIndex(int index);				// Returns card data at a given index
	int GetCostAtIndex(int index);					// Returns the coin cost to retrieve a card at a given index
	void Print();									// Output each card in the hand to cout
private:
	Card* cards;									// The content of the hand
	Deck* deck;										// The associated deck from which to draw cards from
};

int testCards();

