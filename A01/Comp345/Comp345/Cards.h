#pragma once
#include <string>

using namespace std;

const int DECK_SIZE = 11;
const int HAND_SIZE = 6;

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
	string name;				// Title of the card
	string image;				// Source file containing card art
	Action* actions;			// The set of action(s) granted by the card
	int actionCount;			// How many actions this card contains
	CardChoice actionChoice;	// If two actions exist, determine whether it is an AND or OR relationship
	Ability* abilities;			// The ability/abilities listed on the card
	int abilityCount;			// How many abilities are on the card
	void Print();				// Output the card's formatted data
};

class Deck {
public:
	Deck();
	Deck(Deck* deck);
	Card* Draw();
	void Print();
private:
	void Generate();
	Card* cards;
	int deckIndex;
};

class Hand {
public:
	Hand(Deck* deck);
	Hand(Hand* hand);
	Card* Exchange(int index);
	Card* GetCardAtIndex(int index);
	int GetCostAtIndex(int index);
	void Print();
private:
	Card* cards;
	Deck* deck;
};

int testCards();