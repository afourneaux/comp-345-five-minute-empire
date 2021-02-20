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
Deck::Deck(const Deck* deck) {
	this->deckIndex = deck->deckIndex;
	this->cards = new Card[DECK_SIZE];

	for (int i = 0; i < DECK_SIZE; i++) {
		this->cards[i] = new Card(deck->cards[i]);
	}
}

// Create the deck and populate it with hardcoded card data
void Deck::Generate()
{
	this->cards = new Card[DECK_SIZE];

	int index = 0;

	this->cards[index].name = "Dire Dragon";
	this->cards[index].image = "card_dire_dragon.png";
	this->cards[index].actionChoice = eChoice_And;
	this->cards[index].actionCount = 2;
	this->cards[index].abilityCount = 1;
	this->cards[index].abilities = new Ability[1];
	this->cards[index].actions = new Action[2];
	this->cards[index].abilities[0].type = eAbility_Flying;
	this->cards[index].actions[0].action = eAction_PlaceArmies;
	this->cards[index].actions[0].actionValue = 3;
	this->cards[index].actions[1].action = eAction_DestroyArmies;
	this->cards[index].actions[1].actionValue = 1;

	index++;

	this->cards[index].name = "Dire Eye";
	this->cards[index].image = "card_dire_eye.png";
	this->cards[index].actionCount = 1;
	this->cards[index].abilityCount = 1;
	this->cards[index].abilities = new Ability[1];
	this->cards[index].actions = new Action[1];
	this->cards[index].abilities[0].type = eAbility_Flying;
	this->cards[index].actions[0].action = eAction_PlaceArmies;
	this->cards[index].actions[0].actionValue = 4;

	index++;

	this->cards[index].name = "Dire Goblin";
	this->cards[index].image = "card_dire_goblin.png";
	this->cards[index].actionCount = 1;
	this->cards[index].abilityCount = 1;
	this->cards[index].abilities = new Ability[1];
	this->cards[index].actions = new Action[1];
	this->cards[index].abilities[0].type = eAbility_Elixir;
	this->cards[index].abilities[0].value = 1;
	this->cards[index].actions[0].action = eAction_MoveArmies;
	this->cards[index].actions[0].actionValue = 5;

	index++;

	this->cards[index].name = "Dire Ogre";
	this->cards[index].image = "card_dire_ogre.png";
	this->cards[index].actionCount = 1;
	this->cards[index].abilityCount = 1;
	this->cards[index].abilities = new Ability[1];
	this->cards[index].actions = new Action[1];
	this->cards[index].abilities[0].type = eAbility_VpPerCoins;
	this->cards[index].abilities[0].value = 1;
	this->cards[index].abilities[0].setTarget = 3;
	this->cards[index].actions[0].action = eAction_MoveArmies;
	this->cards[index].actions[0].actionValue = 2;

	index++;

	this->cards[index].name = "Lake";
	this->cards[index].image = "card_lake.png";
	this->cards[index].actionCount = 2;
	this->cards[index].actionChoice = eChoice_Or;
	this->cards[index].abilityCount = 1;
	this->cards[index].abilities = new Ability[1];
	this->cards[index].actions = new Action[2];
	this->cards[index].abilities[0].type = eAbility_VpPerCardName;
	this->cards[index].abilities[0].value = 1;
	this->cards[index].abilities[0].setTarget = 1;
	this->cards[index].abilities[0].setName = "Forest";
	this->cards[index].abilities[0].countSetOnce = false;
	this->cards[index].actions[0].action = eAction_PlaceArmies;
	this->cards[index].actions[0].actionValue = 2;
	this->cards[index].actions[1].action = eAction_MoveArmies;
	this->cards[index].actions[1].actionValue = 3;

	index++;

	this->cards[index].name = "Forest Elf";
	this->cards[index].image = "card_forest_elf.png";
	this->cards[index].actionCount = 2;
	this->cards[index].actionChoice = eChoice_Or;
	this->cards[index].abilityCount = 1;
	this->cards[index].abilities = new Ability[1];
	this->cards[index].actions = new Action[2];
	this->cards[index].abilities[0].type = eAbility_PlusOneArmy;
	this->cards[index].actions[0].action = eAction_PlaceArmies;
	this->cards[index].actions[0].actionValue = 3;
	this->cards[index].actions[1].action = eAction_MoveArmies;
	this->cards[index].actions[1].actionValue = 2;

	index++;

	this->cards[index].name = "Forest Gnome";
	this->cards[index].image = "card_forest_gnome.png";
	this->cards[index].actionCount = 1;
	this->cards[index].abilityCount = 1;
	this->cards[index].abilities = new Ability[1];
	this->cards[index].actions = new Action[1];
	this->cards[index].abilities[0].type = eAbility_Elixir;
	this->cards[index].abilities[0].value = 3;
	this->cards[index].actions[0].action = eAction_MoveArmies;
	this->cards[index].actions[0].actionValue = 2;

	index++;

	this->cards[index].name = "Forest Tree Town";
	this->cards[index].image = "card_forest_tree_town.png";
	this->cards[index].actionCount = 1;
	this->cards[index].abilityCount = 1;
	this->cards[index].abilities = new Ability[1];
	this->cards[index].actions = new Action[1];
	this->cards[index].abilities[0].type = eAbility_PlusOneMove;
	this->cards[index].actions[0].action = eAction_BuildCity;

	index++;

	this->cards[index].name = "Graveyard";
	this->cards[index].image = "card_graveyard.png";
	this->cards[index].actionCount = 1;
	this->cards[index].abilityCount = 1;
	this->cards[index].abilities = new Ability[1];
	this->cards[index].actions = new Action[1];
	this->cards[index].abilities[0].type = eAbility_VpPerCardName;
	this->cards[index].abilities[0].value = 1;
	this->cards[index].abilities[0].setTarget = 1;
	this->cards[index].abilities[0].setName = "Cursed";
	this->cards[index].abilities[0].countSetOnce = false;
	this->cards[index].actions[0].action = eAction_BuildCity;

	index++;

	this->cards[index].name = "Mountain Dwarf";
	this->cards[index].image = "card_mountain_dwarf.png";
	this->cards[index].actionChoice = eChoice_And;
	this->cards[index].actionCount = 2;
	this->cards[index].abilityCount = 1;
	this->cards[index].abilities = new Ability[1];
	this->cards[index].actions = new Action[2];
	this->cards[index].abilities[0].type = eAbility_VpPerCardName;
	this->cards[index].abilities[0].value = 3;
	this->cards[index].abilities[0].setTarget = 2;
	this->cards[index].abilities[0].setName = "Mountain";
	this->cards[index].abilities[0].countSetOnce = true;
	this->cards[index].actions[0].action = eAction_PlaceArmies;
	this->cards[index].actions[0].actionValue = 2;
	this->cards[index].actions[1].action = eAction_DestroyArmies;
	this->cards[index].actions[1].actionValue = 1;

	index++;

	this->cards[index].name = "Mountain Treasury";
	this->cards[index].image = "card_mountain_treasury.png";
	this->cards[index].actionCount = 1;
	this->cards[index].abilityCount = 2;
	this->cards[index].abilities = new Ability[2];
	this->cards[index].actions = new Action[1];
	this->cards[index].abilities[0].type = eAbility_Elixir;
	this->cards[index].abilities[0].value = 1;
	this->cards[index].abilities[1].type = eAbility_Coins;
	this->cards[index].abilities[1].value = 2;
	this->cards[index].actions[0].action = eAction_MoveArmies;
	this->cards[index].actions[0].actionValue = 3;
}

// Retrieve the top card and remove it from the deck
Card* Deck::Draw()
{
	// If the deck is empty, return a null pointer
	if (this->deckIndex == DECK_SIZE) {
		cout << "ERROR: Deck::Draw attempting to draw a card from an empty deck" << endl;
		return nullptr;
	}
	return &this->cards[this->deckIndex++];
}

// Assignment operator
Deck& Deck::operator= (const Deck& deck) {
	// Check for self-assignment
	if (this == &deck) {
		return *this;
	}

	this->deckIndex = deck.deckIndex;
	this->cards = new Card[DECK_SIZE];

	for (int i = 0; i < DECK_SIZE; i++) {
		this->cards[i] = new Card(deck.cards[i]);
	}

	return *this;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const Deck& deck) {
	out << "Original deck size: " << DECK_SIZE << endl;
	out << "Total cards dealt: " << deck.deckIndex << endl;
	out << "Cards remaining in the deck: " << DECK_SIZE - deck.deckIndex << endl;
	out << "Card descriptions:" << endl;
	for (int i = deck.deckIndex; i < DECK_SIZE; i++) {
		out << deck.cards[i];
		out << endl;
	}
	return out;
}

/*******
  HAND
 *******/

// Default constructor
Hand::Hand(Deck* deck) {
	this->deck = deck;
	this->cards = new Card[HAND_SIZE];

	// Deal HAND_SIZE cards into the hand from the provided deck
	for (int i = 0; i < HAND_SIZE; i++) {
		this->cards[i] = *this->deck->Draw();
	}
}

// Copy constructor
Hand::Hand(const Hand* hand) {
	this->deck = hand->deck; // Keep the assignment to the same deck
	this->cards = new Card[HAND_SIZE];
	for (int i = 0; i < HAND_SIZE; i++) {
		this->cards[i] = new Card(hand->cards[i]);
	}
}

/*
Hand::~Hand() {
	delete[] this->cards;
	this->deck = nullptr;
}*/

// Spend coins to obtain a card
// Assume coin count in player has already been validated by the calling function
Card* Hand::Exchange(const int index, Player player)
{
	int cost = this->GetCostAtIndex(index);
	player.payCoin(&cost);
	Card* card = &this->cards[index];
	this->cards[index] = *this->deck->Draw();
	return card;
}

// Returns card data at a given index
Card* Hand::GetCardAtIndex(const int index) const
{
	if (index < 0 || index >= HAND_SIZE) {
		cout << "ERROR: Hand::GetCardAtIndex attempting to get card at index " << index << ". Valid values: 0 - " << HAND_SIZE << endl;
		return nullptr;
	}
	return &this->cards[index];
}

// Returns the coin cost to retrieve a card at a given index
// Card costs are 0, 1, 1, 2, 2, 3
// This translates to the card's position / 2 (rounded down)
int Hand::GetCostAtIndex(const int index) const
{
	if (index < 0 || index >= HAND_SIZE) {
		cout << "ERROR: Hand::GetCostAtIndex attempting to get cost at index " << index << ". Valid values: 0 - " << HAND_SIZE << endl;
		return -1;
	}
	return (index + 1) / 2;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const Hand& hand) {
	for (int i = 0; i < HAND_SIZE; i++) {
		out << "*****SLOT " << i + 1 << endl;
		out << "Card cost: " << hand.GetCostAtIndex(i) << endl;
		out << *hand.GetCardAtIndex(i);
		out << endl;
	}
	return out;
}

// Assignment operator
Hand& Hand::operator= (const Hand& hand) {
	// Check for self-assignment
	if (this == &hand) {
		return *this;
	}
	this->deck = hand.deck; // Keep the assignment to the same deck
	this->cards = new Card[HAND_SIZE];
	for (int i = 0; i < HAND_SIZE; i++) {
		this->cards[i] = new Card(hand.cards[i]);
	}

	return *this;
}

/*******
  CARD
 *******/

// Default constructor
Card::Card() {

}

// Copy Constructor
Card::Card(const Card* card) {
	this->name = card->name;
	this->image = card->image;
	this->actionChoice = card->actionChoice;
	this->actionCount = card->actionCount;
	this->abilityCount = card->abilityCount;
	this->abilities = new Ability[card->abilityCount];
	this->actions = new Action[card->actionCount];
	// Copy actions
	for (int i = 0; i < this->actionCount; i++) {
		this->actions[i].action = card->actions[i].action;
		this->actions[i].actionValue = card->actions[i].actionValue;
	}
	// Copy abilities
	for (int i = 0; i < this->abilityCount; i++) {
		this->abilities[i].type = card->abilities[i].type;
		this->abilities[i].value = card->abilities[i].value;
		this->abilities[i].setName = card->abilities[i].setName;
		this->abilities[i].setTarget = card->abilities[i].setTarget;
		this->abilities[i].countSetOnce = card->abilities[i].countSetOnce;
	}
}

// Assignment operator
Card& Card::operator= (const Card& card) {
	// Check for self-assignment
	if (this == &card) {
		return *this;
	}

	this->name = card.name;
	this->image = card.image;
	this->actionChoice = card.actionChoice;
	this->actionCount = card.actionCount;
	this->abilityCount = card.abilityCount;
	this->abilities = new Ability[card.abilityCount];
	this->actions = new Action[card.actionCount];
	// Copy actions
	for (int i = 0; i < this->actionCount; i++) {
		this->actions[i].action = card.actions[i].action;
		this->actions[i].actionValue = card.actions[i].actionValue;
	}
	// Copy abilities
	for (int i = 0; i < this->abilityCount; i++) {
		this->abilities[i].type = card.abilities[i].type;
		this->abilities[i].value = card.abilities[i].value;
		this->abilities[i].setName = card.abilities[i].setName;
		this->abilities[i].setTarget = card.abilities[i].setTarget;
		this->abilities[i].countSetOnce = card.abilities[i].countSetOnce;
	}

	return *this;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const Card& card) {
	// Print identifying information
	out << "===============" << endl;
	out << card.name << endl;
	out << "Image source: " << card.image << endl;
	// Print ability/abilities
	out << "===ABILITIES===" << endl;
	for (int i = 0; i < card.abilityCount; i++) {
		out << card.abilities[i] << endl;
	}
	// Print action(s)
	out << "====ACTIONS====" << endl;
	for (int i = 0; i < card.actionCount; i++) {
		out << card.actions[i];
		if (i < card.actionCount - 1) {
			switch (card.actionChoice) {
			case eChoice_And:
				out << " AND ";
				break;
			case eChoice_Or:
				out << " OR ";
				break;
			}
		}
	}
	out << endl;
	out << "===============" << endl;
	return out;
}

/*******
  ACTION
 *******/

// Assignment operator
Action& Action::operator= (const Action& action) {
	// Check for self-assignment
	if (this == &action) {
		return *this;
	}

	this->action = action.action;
	this->actionValue = action.actionValue;

	return *this;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const Action& action) {
	switch (action.action) {
	case eAction_BuildCity:
		out << "Build City";
		break;
	case eAction_DestroyArmies:
		out << "Destroy " << action.actionValue;
		if (action.actionValue == 1) {
			out << " Army";
		}
		else {
			out << " Armies";
		}
		break;
	case eAction_MoveArmies:
		out << "Move " << action.actionValue;
		if (action.actionValue == 1) {
			out << " Army";
		}
		else {
			out << " Armies";
		}
		break;
	case eAction_PlaceArmies:
		out << "Place " << action.actionValue;
		if (action.actionValue == 1) {
			out << " Army";
		}
		else {
			out << " Armies";
		}
		break;
	case eAction_None:
		out << "No Action";
		break;
	}
	return out;
}

/*******
  ABILITY
 *******/

Ability& Ability::operator= (const Ability& ability) {
	// Check for self-assignment
	if (this == &ability) {
		return *this;
	}

	this->type = ability.type;
	this->value = ability.value;
	this->setName = ability.setName;
	this->setTarget = ability.setTarget;
	this->countSetOnce = ability.countSetOnce;

	return *this;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const Ability& ability) {
	switch (ability.type) {
	case eAbility_PlusOneMove:
		out << "Plus One Movement";
		break;
	case eAbility_PlusOneArmy:
		out << "Plus One Army";
		break;
	case eAbility_Flying:
		out << "Flying";
		break;
	case eAbility_Coins:
		if (ability.value == 1) {
			out << ability.value << " Coin";
		}
		else {
			out << ability.value << " Coins";
		}
		break;
	case eAbility_Elixir:
		if (ability.value == 1) {
			out << ability.value << " Elixir";
		}
		else {
			out << ability.value << " Elixirs";
		}
		break;
	case eAbility_VpPerCardName:
		out << "+" << ability.value << "VP ";
		if (ability.countSetOnce) {
			out << "if you have ";
		}
		else {
			out << "per ";
		}
		if (ability.setTarget == 1) {
			out << ability.setName << " card";
		}
		else {
			out << ability.setTarget << " " << ability.setName << " cards";
		}
		break;
	case eAbility_VpPerCoins:
		out << "+" << ability.value << "VP per ";
		if (ability.setTarget == 1) {
			out << "coin";
		}
		else {
			out << ability.setTarget << " coins";
		}
	case eAbility_None:
		out << "No Ability";
		break;
	}
	return out;
}
