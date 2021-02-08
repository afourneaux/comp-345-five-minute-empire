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

	index++;

	(&this->cards[index])->name = "Dire Eye";
	(&this->cards[index])->image = "card_dire_eye.png";
	(&this->cards[index])->actionCount = 1;
	(&this->cards[index])->abilityCount = 1;
	(&this->cards[index])->abilities = new Ability[1];
	(&this->cards[index])->actions = new Action[1];
	(&(&this->cards[index])->abilities[0])->type = eAbility_Flying;
	(&(&this->cards[index])->actions[0])->action = eAction_PlaceArmies;
	(&(&this->cards[index])->actions[0])->actionValue = 4;

	index++;

	(&this->cards[index])->name = "Dire Goblin";
	(&this->cards[index])->image = "card_dire_goblin.png";
	(&this->cards[index])->actionCount = 1;
	(&this->cards[index])->abilityCount = 1;
	(&this->cards[index])->abilities = new Ability[1];
	(&this->cards[index])->actions = new Action[1];
	(&(&this->cards[index])->abilities[0])->type = eAbility_Elixir;
	(&(&this->cards[index])->abilities[0])->value = 1;
	(&(&this->cards[index])->actions[0])->action = eAction_MoveArmies;
	(&(&this->cards[index])->actions[0])->actionValue = 5;

	index++;

	(&this->cards[index])->name = "Dire Ogre";
	(&this->cards[index])->image = "card_dire_ogre.png";
	(&this->cards[index])->actionCount = 1;
	(&this->cards[index])->abilityCount = 1;
	(&this->cards[index])->abilities = new Ability[1];
	(&this->cards[index])->actions = new Action[1];
	(&(&this->cards[index])->abilities[0])->type = eAbility_VpPerCoins;
	(&(&this->cards[index])->abilities[0])->value = 1;
	(&(&this->cards[index])->abilities[0])->setTarget = 3;
	(&(&this->cards[index])->actions[0])->action = eAction_MoveArmies;
	(&(&this->cards[index])->actions[0])->actionValue = 2;

	index++;

	(&this->cards[index])->name = "Lake";
	(&this->cards[index])->image = "card_lake.png";
	(&this->cards[index])->actionCount = 2;
	(&this->cards[index])->actionChoice = eChoice_Or;
	(&this->cards[index])->abilityCount = 1;
	(&this->cards[index])->abilities = new Ability[1];
	(&this->cards[index])->actions = new Action[2];
	(&(&this->cards[index])->abilities[0])->type = eAbility_VpPerCardName;
	(&(&this->cards[index])->abilities[0])->value = 1;
	(&(&this->cards[index])->abilities[0])->setTarget = 1;
	(&(&this->cards[index])->abilities[0])->setName = "Forest";
	(&(&this->cards[index])->abilities[0])->countSetOnce = false;
	(&(&this->cards[index])->actions[0])->action = eAction_PlaceArmies;
	(&(&this->cards[index])->actions[0])->actionValue = 2;
	(&(&this->cards[index])->actions[1])->action = eAction_MoveArmies;
	(&(&this->cards[index])->actions[1])->actionValue = 3;

	index++;

	(&this->cards[index])->name = "Forest Elf";
	(&this->cards[index])->image = "card_forest_elf.png";
	(&this->cards[index])->actionCount = 2;
	(&this->cards[index])->actionChoice = eChoice_Or;
	(&this->cards[index])->abilityCount = 1;
	(&this->cards[index])->abilities = new Ability[1];
	(&this->cards[index])->actions = new Action[2];
	(&(&this->cards[index])->abilities[0])->type = eAbility_PlusOneArmy;
	(&(&this->cards[index])->actions[0])->action = eAction_PlaceArmies;
	(&(&this->cards[index])->actions[0])->actionValue = 3;
	(&(&this->cards[index])->actions[1])->action = eAction_MoveArmies;
	(&(&this->cards[index])->actions[1])->actionValue = 2;

	index++;

	(&this->cards[index])->name = "Forest Gnome";
	(&this->cards[index])->image = "card_forest_gnome.png";
	(&this->cards[index])->actionCount = 1;
	(&this->cards[index])->abilityCount = 1;
	(&this->cards[index])->abilities = new Ability[1];
	(&this->cards[index])->actions = new Action[1];
	(&(&this->cards[index])->abilities[0])->type = eAbility_Elixir;
	(&(&this->cards[index])->abilities[0])->value = 3;
	(&(&this->cards[index])->actions[0])->action = eAction_MoveArmies;
	(&(&this->cards[index])->actions[0])->actionValue = 2;

	index++;

	(&this->cards[index])->name = "Forest Tree Town";
	(&this->cards[index])->image = "card_forest_tree_town.png";
	(&this->cards[index])->actionCount = 1;
	(&this->cards[index])->abilityCount = 1;
	(&this->cards[index])->abilities = new Ability[1];
	(&this->cards[index])->actions = new Action[1];
	(&(&this->cards[index])->abilities[0])->type = eAbility_PlusOneMove;
	(&(&this->cards[index])->actions[0])->action = eAction_BuildCity;

	index++;

	(&this->cards[index])->name = "Graveyard";
	(&this->cards[index])->image = "card_graveyard.png";
	(&this->cards[index])->actionCount = 1;
	(&this->cards[index])->abilityCount = 1;
	(&this->cards[index])->abilities = new Ability[1];
	(&this->cards[index])->actions = new Action[1];
	(&(&this->cards[index])->abilities[0])->type = eAbility_VpPerCardName;
	(&(&this->cards[index])->abilities[0])->value = 1;
	(&(&this->cards[index])->abilities[0])->setTarget = 1;
	(&(&this->cards[index])->abilities[0])->setName = "Cursed";
	(&(&this->cards[index])->abilities[0])->countSetOnce = false;
	(&(&this->cards[index])->actions[0])->action = eAction_BuildCity;

	index++;

	(&this->cards[index])->name = "Mountain Dwarf";
	(&this->cards[index])->image = "card_mountain_dwarf.png";
	(&this->cards[index])->actionChoice = eChoice_And;
	(&this->cards[index])->actionCount = 2;
	(&this->cards[index])->abilityCount = 1;
	(&this->cards[index])->abilities = new Ability[1];
	(&this->cards[index])->actions = new Action[2];
	(&(&this->cards[index])->abilities[0])->type = eAbility_VpPerCardName;
	(&(&this->cards[index])->abilities[0])->value = 3;
	(&(&this->cards[index])->abilities[0])->setTarget = 2;
	(&(&this->cards[index])->abilities[0])->setName = "Mountain";
	(&(&this->cards[index])->abilities[0])->countSetOnce = true;
	(&(&this->cards[index])->actions[0])->action = eAction_PlaceArmies;
	(&(&this->cards[index])->actions[0])->actionValue = 2;
	(&(&this->cards[index])->actions[1])->action = eAction_DestroyArmies;
	(&(&this->cards[index])->actions[1])->actionValue = 1;

	index++;

	(&this->cards[index])->name = "Mountain Treasury";
	(&this->cards[index])->image = "card_mountain_treasury.png";
	(&this->cards[index])->actionCount = 1;
	(&this->cards[index])->abilityCount = 2;
	(&this->cards[index])->abilities = new Ability[2];
	(&this->cards[index])->actions = new Action[1];
	(&(&this->cards[index])->abilities[0])->type = eAbility_Elixir;
	(&(&this->cards[index])->abilities[0])->value = 1;
	(&(&this->cards[index])->abilities[1])->type = eAbility_Coins;
	(&(&this->cards[index])->abilities[1])->value = 2;
	(&(&this->cards[index])->actions[0])->action = eAction_MoveArmies;
	(&(&this->cards[index])->actions[0])->actionValue = 3;
}

// Get the top card and remove it from the deck
Card* Deck::Draw()
{
	// If the deck is empty, return a null pointer
	if (this->deckIndex == DECK_SIZE) {
		cout << "ERROR: Deck::Draw attempting to draw a card from an empty deck" << endl;
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
	for (int i = this->deckIndex; i < DECK_SIZE; i++) {
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
		cout << "ERROR: Hand::GetCardAtIndex attempting to get card at index " << index << ". Valid values: 0 - " << HAND_SIZE << endl;
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
		cout << "ERROR: Hand::GetCostAtIndex attempting to get cost at index " << index << ". Valid values: 0 - " << HAND_SIZE << endl;
		return -1;
	}
	return (index + 1) / 2;
}

void Hand::Print() {
	cout << "*******PRINTING HAND CONTENTS*******" << endl;
	for (int i = 0; i < HAND_SIZE; i++) {
		cout << "*****SLOT " << i + 1 << endl;
		cout << "Card cost: " << this->GetCostAtIndex(i) << endl;
		this->GetCardAtIndex(i)->Print();
	}
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
			value += "if you have ";
		}
		else {
			value += "per ";
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
