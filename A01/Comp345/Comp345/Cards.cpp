#include "Cards.h"
#include <iostream>

/*******
  DECK
 *******/

// Default constructor
Deck::Deck() {
	this->deckIndex = 0;
	this->Generate();
}

// Copy constructor
Deck::Deck(Deck* deck) {

}

// Create the deck and populate it with hardcoded card data
void Deck::Generate()
{
	this->cards = new Card[DECK_SIZE];

	int index = 0;

	(&this->cards[index])->name = "Dire Dragon";
	(&this->cards[index])->image = "card_dire_dragon.png";
	(&this->cards[index])->actionChoice = eChoice_And;
	(&this->cards[index])->actionCount = 2;
	(&this->cards[index])->abilityCount = 1;
	(&this->cards[index])->abilities = new Ability[1];
	(&this->cards[index])->actions = new Action[2];
	(&(&this->cards[index])->abilities[0])->type = eAbility_Flying;
	(&(&this->cards[index])->actions[0])->action = eAction_PlaceArmies;
	(&(&this->cards[index])->actions[0])->actionValue = 3;
	(&(&this->cards[index])->actions[1])->action = eAction_DestroyArmies;
	(&(&this->cards[index])->actions[1])->actionValue = 1;
}

// Get the top card and remove it from the deck
Card* Deck::Draw()
{
	// If the deck is empty, return a null pointer
	if (this->deckIndex == DECK_SIZE) {
		return nullptr;
	}
	return &this->cards[this->deckIndex++];
}

void Deck::Print() {
	cout << "*******PRINTING DECK CONTENTS*******" << endl;
	cout << "Starting deck size: " << DECK_SIZE << endl;
	cout << "Total cards dealt: " << this->deckIndex << endl;
	cout << "Cards remaining in the deck: " << DECK_SIZE - this->deckIndex << endl;
	cout << "Card descriptions:" << endl;
	for (int i = this->deckIndex; i < DECK_SIZE - this->deckIndex; i++) {
		(&this->cards[i])->Print();
	}
}

/*******
  HAND
 *******/

// Default constructor
Hand::Hand(Deck* deck) {
	this->deck = deck;
	this->cards = new Card[HAND_SIZE];

	for (int i = 0; i < HAND_SIZE; i++) {
		this->cards[i] = *this->deck->Draw();
	}
}

// Copy constructor
Hand::Hand(Hand* hand) {

}

Card* Hand::Exchange(int index/*, Player player */)
{
	int cost = this->GetCostAtIndex(index);
	// TODO: Logic to make the player pay for the card
	Card* card = &this->cards[index];
	this->cards[index] = *this->deck->Draw();
	return card;
}

Card* Hand::GetCardAtIndex(int index)
{
	if (index < 0 || index >= HAND_SIZE) {
		// TODO: Handle index out of bounds
		return nullptr;
	}
	return &this->cards[index];
}

// Card costs are 0, 1, 1, 2, 2, 3
// This translates to the card's position / 2 (rounded down)
int Hand::GetCostAtIndex(int index)
{
	if (index < 0 || index >= HAND_SIZE) {
		// TODO: Handle index out of bounds
		return -1;
	}
	return (index + 1) / 2;
}

/*******
  CARD
 *******/

void Card::Print() {
	cout << "===============" << endl; 
	cout << this->name << endl;
	cout << "Image source: " << this->image << endl;
	// Print action(s)
	cout << "====ACTIONS====" << endl;
	for (int i = 0; i < this->actionCount; i++) {
		cout << (&this->actions[i])->ToString();
		if (i < this->actionCount - 1) {
			switch (this->actionChoice) {
			case eChoice_And:
				cout << " AND ";
				break;
			case eChoice_Or:
				cout << " OR ";
				break;
			}
		}
	}
	cout << endl;
	// Print ability/abilities
	cout << "===ABILITIES===" << endl;
	for (int i = 0; i < this->abilityCount; i++) {
		cout << (&this->abilities[i])->ToString();
		cout << endl;
	}
}

/*******
  ACTION
 *******/

string Action::ToString()
{
	string value;
	switch (this->action) {
	case eAction_BuildCity:
		value = "Build City";
		break;
	case eAction_DestroyArmies:
		value = "Destroy " + to_string(this->actionValue);
		if (this->actionValue == 1) {
			value += " Army";
		}
		else {
			value += " Armies";
		}
		break;
	case eAction_MoveArmies:
		value = "Move " + to_string(this->actionValue);
		if (this->actionValue == 1) {
			value += " Army";
		}
		else {
			value += " Armies";
		}
		break;
	case eAction_PlaceArmies:
		value = "Place " + to_string(this->actionValue);
		if (this->actionValue == 1) {
			value += " Army";
		}
		else {
			value += " Armies";
		}
		break;
	case eAction_None:
		value = "No Action";
		break;
	}
	return value;
}

/*******
  ABILITY
 *******/

string Ability::ToString()
{
	string value;
	switch (this->type) {
	case eAbility_PlusOneMove:
		value = "Plus One Movement";
		break;
	case eAbility_PlusOneArmy:
		value = "Plus One Army";
		break;
	case eAbility_Flying:
		value = "Flying";
		break;
	case eAbility_Coins:
		if (this->value == 1) {
			value = to_string(this->value) + " Coin";
		}
		else {
			value = to_string(this->value) + " Coins";
		}
		break;
	case eAbility_Elixir:
		if (this->value == 1) {
			value = to_string(this->value) + " Elixir";
		}
		else {
			value = to_string(this->value) + " Elixirs";
		}
		break;
	case eAbility_VpPerCardName:
		value = "+" + to_string(this->value) + "VP ";
		if (this->countSetOnce) {
			value += " if you have ";
		}
		else {
			value += " per ";
		}
		if (this->setTarget == 1) {
			value += this->setName + " card";
		}
		else {
			value += to_string(this->setTarget) + " " + this->setName + " cards";
		}
		break;
	case eAbility_VpPerCoins:
		value = "+" + to_string(this->value) + "VP per ";
		if (this->setTarget == 1) {
			value += "coin";
		}
		else {
			value += to_string(this->setTarget) + " coins";
		}
	case eAbility_None:
		value = "No Ability";
		break;
	}

	return value;
}
