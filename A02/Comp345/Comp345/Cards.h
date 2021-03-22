#pragma once
#include <string>
#include "Player.h"

using namespace std;

const int HAND_SIZE = 6;	// The number of face-up cards in the hand
const int ELIXIR_BONUS = 2;	// Bonus score awarded for having the most elixirs

struct Player;

// The different possible actions granted by a card
enum CardAction {
	eAction_None,
	eAction_PlaceArmies,
	eAction_MoveArmies,
	eAction_BuildCity,
	eAction_DestroyArmies
};

// If a card has multiple actions, determine whether they can do both or choose one
enum CardChoice {
	eChoice_None,
	eChoice_And,
	eChoice_Or
};

// The ability types granted by cards
enum CardAbility {
	eAbility_None,
	eAbility_PlusOneMove,
	eAbility_PlusOneArmy,
	eAbility_Flying,
	eAbility_Elixir,
	eAbility_Coins,
	eAbility_VpPerCardName,
	eAbility_VpPerCoins,
	eAbility_VpPerFlying,
	eAbility_Immune
};

struct Action {
	CardAction action;			// The type of action allowed by the card
	int actionValue;			// The value associated to the card's action, for example "move *2* armies"Ability
	Action& operator= (const Action& action);							// Assignment operator
	friend ostream& operator<< (ostream& out, const Action& action);	// Stream insertion operator
};

struct Ability {
	CardAbility type;			// The type of ability granted by the card
	int value;					// The value associated to the ability
	string setName;				// If the card grants VP Per Card Set, what name does it target?
	int setTarget;				// If the card grants VP Per Card Set, how many cards does the holder need?
	bool countSetOnce;			// If true, VP for having a card set is only granted once
	Ability& operator= (const Ability& ability);						// Assignment operator
	friend ostream& operator<< (ostream& out, const Ability& ability);	// Stream insertion operator
};

struct Card {
	Card();						// Default constructor
	Card(const Card* card);		// Copy constructor
	~Card();					// Destructor
	string name;				// Title of the card
	string image;				// Source file containing card art
	Action* actions;			// The set of action(s) granted by the card
	int actionCount;			// How many actions this card contains
	CardChoice actionChoice;	// If two actions exist, determine whether it is an AND or OR relationship
	Ability* abilities;			// The ability/abilities listed on the card
	int abilityCount;			// How many abilities are on the card
	Card& operator= (const Card& card);								// Assignment operator
	friend ostream& operator<< (ostream& out, const Card& card);	// Stream insertion operator
};

class Deck {
public:
	Deck(int num_player);			// Default constructor
	Deck(const Deck* deck);			// Copy constructor
	~Deck();						// Destructor
	Card* Draw();					// Return and remove the first card from the deck
	Deck& operator= (const Deck& deck);								// Assignment operator
	friend ostream& operator<< (ostream& out, const Deck& deck);	// Stream insertion operator
	int GetSize() const;			// Get the number of cards remaining in the deck
private:
	void Generate(int playerCount);	// Populate the deck with hard-coded cards
	void Shuffle();					// Reorder the cards into a random order
	vector<Card*> cards;			// The contents of the deck
};

class Hand {
public:
	Hand(Deck* deck);									// Default constructor
	Hand(const Hand* hand);								// Copy constructor
	~Hand();											// Destructor
	Card* Exchange(const int index);					// Take a card from the hand and shift all other cards in the hand down one index
	Card* GetCardAtIndex(const int index) const;		// Returns card data at a given index
	int GetCostAtIndex(const int index) const;			// Returns the coin cost to retrieve a card at a given index
	Hand& operator= (const Hand& hand);								// Assignment operator
	friend ostream& operator<< (ostream& out, const Hand& hand);	// Stream insertion operator
private:
	Card* cards[HAND_SIZE];								// The contents of the hand
	Deck* deck;											// The associated deck from which to draw cards from
};