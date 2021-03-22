#include "Cards.h"
#include <iostream>
#include <algorithm>
#include <random>

/*******
  DECK
 *******/

 // Constructor
Deck::Deck(int num_player) {
	Generate(num_player);
	Shuffle();
}

// Copy constructor
Deck::Deck(const Deck* deck) {
	for (int i = 0; i < deck->GetSize(); i++) {
		cards.push_back(new Card(deck->cards.at(i)));
	}
}

// Destructor
Deck::~Deck() {
	while (cards.empty() == false) {
		cards.pop_back();
	}
}

// Get the number of cards remaining in the deck
int Deck::GetSize() const
{
	return cards.size();
}

// Create the deck and populate it with hardcoded card data
void Deck::Generate(int num_player)
{
	Card* card = new Card();
	card->name = "Dire Dragon";
	card->image = "card_dire_dragon.png";
	card->actionChoice = eChoice_And;
	card->actionCount = 2;
	card->abilityCount = 1;
	card->abilities = new Ability[1];
	card->actions = new Action[2];
	card->abilities[0].type = eAbility_Flying;
	card->actions[0].action = eAction_PlaceArmies;
	card->actions[0].actionValue = 3;
	card->actions[1].action = eAction_DestroyArmies;
	card->actions[1].actionValue = 1;
	cards.push_back(card);

	card = new Card();
	card->name = "Dire Eye";
	card->image = "card_dire_eye.png";
	card->actionCount = 1;
	card->abilityCount = 1;
	card->abilities = new Ability[1];
	card->actions = new Action[1];
	card->abilities[0].type = eAbility_Flying;
	card->actions[0].action = eAction_PlaceArmies;
	card->actions[0].actionValue = 4;
	cards.push_back(card);

	card = new Card();
	card->name = "Dire Goblin";
	card->image = "card_dire_goblin.png";
	card->actionCount = 1;
	card->abilityCount = 1;
	card->abilities = new Ability[1];
	card->actions = new Action[1];
	card->abilities[0].type = eAbility_Elixir;
	card->abilities[0].value = 1;
	card->actions[0].action = eAction_MoveArmies;
	card->actions[0].actionValue = 5;
	cards.push_back(card);

	card = new Card();
	card->name = "Dire Ogre";
	card->image = "card_dire_ogre.png";
	card->actionCount = 1;
	card->abilityCount = 1;
	card->abilities = new Ability[1];
	card->actions = new Action[1];
	card->abilities[0].type = eAbility_VpPerCoins;
	card->abilities[0].value = 1;
	card->abilities[0].setTarget = 3;
	card->actions[0].action = eAction_MoveArmies;
	card->actions[0].actionValue = 2;
	cards.push_back(card);

	card = new Card();
	card->name = "Lake";
	card->image = "card_lake.png";
	card->actionCount = 2;
	card->actionChoice = eChoice_Or;
	card->abilityCount = 1;
	card->abilities = new Ability[1];
	card->actions = new Action[2];
	card->abilities[0].type = eAbility_VpPerCardName;
	card->abilities[0].value = 1;
	card->abilities[0].setTarget = 1;
	card->abilities[0].setName = "Forest";
	card->abilities[0].countSetOnce = false;
	card->actions[0].action = eAction_PlaceArmies;
	card->actions[0].actionValue = 2;
	card->actions[1].action = eAction_MoveArmies;
	card->actions[1].actionValue = 3;
	cards.push_back(card);

	card = new Card();
	card->name = "Forest Elf";
	card->image = "card_forest_elf.png";
	card->actionCount = 2;
	card->actionChoice = eChoice_Or;
	card->abilityCount = 1;
	card->abilities = new Ability[1];
	card->actions = new Action[2];
	card->abilities[0].type = eAbility_PlusOneArmy;
	card->actions[0].action = eAction_PlaceArmies;
	card->actions[0].actionValue = 3;
	card->actions[1].action = eAction_MoveArmies;
	card->actions[1].actionValue = 2;
	cards.push_back(card);

	card = new Card();
	card->name = "Forest Gnome";
	card->image = "card_forest_gnome.png";
	card->actionCount = 1;
	card->abilityCount = 1;
	card->abilities = new Ability[1];
	card->actions = new Action[1];
	card->abilities[0].type = eAbility_Elixir;
	card->abilities[0].value = 3;
	card->actions[0].action = eAction_MoveArmies;
	card->actions[0].actionValue = 2;
	cards.push_back(card);

	card = new Card();
	card->name = "Forest Tree Town";
	card->image = "card_forest_tree_town.png";
	card->actionCount = 1;
	card->abilityCount = 1;
	card->abilities = new Ability[1];
	card->actions = new Action[1];
	card->abilities[0].type = eAbility_PlusOneMove;
	card->actions[0].action = eAction_BuildCity;
	card->actions[0].actionValue = 1;
	cards.push_back(card);

	card = new Card();
	card->name = "Graveyard";
	card->image = "card_graveyard.png";
	card->actionCount = 1;
	card->abilityCount = 1;
	card->abilities = new Ability[1];
	card->actions = new Action[1];
	card->abilities[0].type = eAbility_VpPerCardName;
	card->abilities[0].value = 1;
	card->abilities[0].setTarget = 1;
	card->abilities[0].setName = "Cursed";
	card->abilities[0].countSetOnce = false;
	card->actions[0].action = eAction_BuildCity;
	card->actions[0].actionValue = 1;
	cards.push_back(card);

	card = new Card();
	card->name = "Noble Hills";
	cards.push_back(card);

	card = new Card();
	card->name = "Noble Knight";
	cards.push_back(card);

	card = new Card();
	card->name = "Noble Unicorn";
	cards.push_back(card);

	card = new Card();
	card->name = "Night Hydra";
	cards.push_back(card);

	card = new Card();
	card->name = "Night Village";
	cards.push_back(card);

	card = new Card();
	card->name = "Forest Pixie";
	cards.push_back(card);

	card = new Card();
	card->name = "Stronghold";
	cards.push_back(card);

	card = new Card();
	card->name = "Ancient Phoenix";
	cards.push_back(card);

	card = new Card();
	card->name = "Ancient Tree Spirit";
	cards.push_back(card);

	card = new Card();
	card->name = "Ancient Woods";
	cards.push_back(card);

	card = new Card();
	card->name = "Ancient Sage";
	cards.push_back(card);

	card = new Card();
	card->name = "Cursed Banshee";
	cards.push_back(card);

	card = new Card();
	card->name = "Cursed Gargoyles";
	cards.push_back(card);

	card = new Card();
	card->name = "Cursed King";
	cards.push_back(card);

	card = new Card();
	card->name = "Cursed Mausolum";
	cards.push_back(card);

	card = new Card();
	card->name = "Cursed Tower";
	cards.push_back(card);

	card = new Card();
	card->name = "Dire Giant";
	cards.push_back(card);

	card = new Card();
	card->name = "Night Wizard";
	cards.push_back(card);

	if (num_player >= 3)
	{
		card = new Card();
		card->name = "Mountain Dwarf";
		card->image = "card_mountain_dwarf.png";
		card->actionChoice = eChoice_And;
		card->actionCount = 2;
		card->abilityCount = 1;
		card->abilities = new Ability[1];
		card->actions = new Action[2];
		card->abilities[0].type = eAbility_VpPerCardName;
		card->abilities[0].value = 3;
		card->abilities[0].setTarget = 2;
		card->abilities[0].setName = "Mountain";
		card->abilities[0].countSetOnce = true;
		card->actions[0].action = eAction_PlaceArmies;
		card->actions[0].actionValue = 2;
		card->actions[1].action = eAction_DestroyArmies;
		card->actions[1].actionValue = 1;
		cards.push_back(card);

		card = new Card();
		card->name = "Mountain Treasury";
		card->image = "card_mountain_treasury.png";
		card->actionCount = 1;
		card->abilityCount = 2;
		card->abilities = new Ability[2];
		card->actions = new Action[1];
		card->abilities[0].type = eAbility_Elixir;
		card->abilities[0].value = 1;
		card->abilities[1].type = eAbility_Coins;
		card->abilities[1].value = 2;
		card->actions[0].action = eAction_MoveArmies;
		card->actions[0].actionValue = 3;
		cards.push_back(card);

		card = new Card();
		card->name = "Arcane Sphinx";
		cards.push_back(card);

		card = new Card();
		card->name = "Arcane Temple";
		cards.push_back(card);

		card = new Card();
		card->name = "Arcane Manticore";
		cards.push_back(card);
	}

	if (num_player >= 4)
	{
		card = new Card();
		card->name = "Castle";
		card->image = "card_castle.png";
		card->actionCount = 1;
		card->abilityCount = 1;
		card->abilities = new Ability[1];
		card->actions = new Action[2];
		card->abilities[0].type = eAbility_Elixir;
		card->abilities[0].value = 1;
		card->actions[0].action = eAction_MoveArmies;
		card->actions[0].actionValue = 3;
		card->actions[1].action = eAction_BuildCity;
		card->actions[1].actionValue = 1;
		cards.push_back(card);

		card = new Card();
		card->name = "Castle";
		card->image = "card_castle.png";
		card->actionCount = 1;
		card->abilityCount = 1;
		card->abilities = new Ability[1];
		card->actions = new Action[2];
		card->abilities[0].type = eAbility_Elixir;
		card->abilities[0].value = 1;
		card->actions[0].action = eAction_MoveArmies;
		card->actions[0].actionValue = 3;
		card->actions[1].action = eAction_BuildCity;
		card->actions[1].actionValue = 1;
		cards.push_back(card);
	}
}

// Retrieve the top card and remove it from the deck
Card* Deck::Draw()
{
	if (cards.empty()) {
		return nullptr;
	}
	Card* draw = cards.back();
	cards.pop_back();
	return draw;
}

// Reorder the Cards vector in a random order
void Deck::Shuffle()
{
	shuffle(cards.begin(), cards.end(), default_random_engine{ random_device{}() });
}

// Assignment operator
Deck& Deck::operator= (const Deck& deck) {
	// Check for self-assignment
	if (this == &deck) {
		return *this;
	}

	for (int i = 0; i < deck.GetSize(); i++) {
		cards.push_back(new Card(deck.cards.at(i)));
	}

	return *this;
}

//Stream insertion operator 
ostream& operator<<(ostream& out, const Deck& deck) {
	out << "Cards remaining in the deck: " << deck.GetSize() << endl;
	out << "Card descriptions:" << endl;
	for (int i = 0; i < deck.GetSize(); i++) {
		out << deck.cards.at(i) << endl;
	}
	return out;
}

/*******
  HAND
 *******/

 // Default constructor
Hand::Hand(Deck* newDeck) {
	deck = newDeck;

	// Deal HAND_SIZE cards into the hand from the provided deck
	for (int i = 0; i < HAND_SIZE; i++) {
		cards[i] = deck->Draw();
	}
}

// Copy constructor
Hand::Hand(const Hand* hand) {
	deck = hand->deck; // Keep the assignment to the same deck
	for (int i = 0; i < HAND_SIZE; i++) {
		cards[i] = hand->cards[i];
	}
}

Hand::~Hand() {
	delete[] cards;
	deck = nullptr;
}

// Take a card from the hand and shift all other cards in the hand down one index
Card* Hand::Exchange(const int index)
{
	if (&cards[index] == nullptr) {
		cout << "ERROR: Trying to exchange with an empty card slot" << endl;
		return nullptr;
	}
	int cost = GetCostAtIndex(index);
	Card* card = new Card(cards[index]);
	// Shift each card down one on the track
	for (int i = index; i < HAND_SIZE - 1; i++) {
		cards[i] = cards[i + 1];
	}
	cards[HAND_SIZE - 1] = deck->Draw();
	return card;
}

// Returns card data at a given index
Card* Hand::GetCardAtIndex(const int index) const
{
	if (index < 0 || index >= HAND_SIZE) {
		cout << "ERROR: Hand::GetCardAtIndex attempting to get card at index " << index << ". Valid values: 0 - " << HAND_SIZE << endl;
		return nullptr;
	}
	return cards[index];
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
		if (hand.GetCardAtIndex(i) == nullptr) {
			continue;
		}
		out << "SLOT " << i << endl;
		out << "Card cost: " << hand.GetCostAtIndex(i) << endl;
		out << *hand.GetCardAtIndex(i) << endl;
	}
	return out;
}

// Assignment operator
Hand& Hand::operator= (const Hand& hand) {
	// Check for self-assignment
	if (this == &hand) {
		return *this;
	}
	deck = hand.deck; // Keep the assignment to the same deck
	for (int i = 0; i < HAND_SIZE; i++) {
		cards[i] = new Card(hand.cards[i]);
	}

	return *this;
}

/*******
  CARD
 *******/

 // Default constructor
Card::Card() {
	abilityCount = 0;
	actionCount = 0;
	actionChoice = eChoice_None;
}

// Copy Constructor
Card::Card(const Card* card) {
	name = card->name;
	image = card->image;
	actionChoice = card->actionChoice;
	actionCount = card->actionCount;
	abilityCount = card->abilityCount;
	abilities = new Ability[card->abilityCount];
	actions = new Action[card->actionCount];
	// Copy actions
	for (int i = 0; i < actionCount; i++) {
		actions[i].action = card->actions[i].action;
		actions[i].actionValue = card->actions[i].actionValue;
	}
	// Copy abilities
	for (int i = 0; i < abilityCount; i++) {
		abilities[i].type = card->abilities[i].type;
		abilities[i].value = card->abilities[i].value;
		abilities[i].setName = card->abilities[i].setName;
		abilities[i].setTarget = card->abilities[i].setTarget;
		abilities[i].countSetOnce = card->abilities[i].countSetOnce;
	}
}

// Destructor
Card::~Card() {
	if (actionCount > 0) {
		delete[] actions;
	}
	if (abilityCount > 0) {
		delete[] abilities;
	}
}

// Assignment operator
Card& Card::operator= (const Card& card) {
	// Check for self-assignment
	if (this == &card) {
		return *this;
	}

	name = card.name;
	image = card.image;
	actionChoice = card.actionChoice;
	actionCount = card.actionCount;
	abilityCount = card.abilityCount;
	abilities = new Ability[card.abilityCount];
	actions = new Action[card.actionCount];
	// Copy actions
	for (int i = 0; i < actionCount; i++) {
		actions[i].action = card.actions[i].action;
		actions[i].actionValue = card.actions[i].actionValue;
	}
	// Copy abilities
	for (int i = 0; i < abilityCount; i++) {
		abilities[i].type = card.abilities[i].type;
		abilities[i].value = card.abilities[i].value;
		abilities[i].setName = card.abilities[i].setName;
		abilities[i].setTarget = card.abilities[i].setTarget;
		abilities[i].countSetOnce = card.abilities[i].countSetOnce;
	}

	return *this;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const Card& card) {
	// Print identifying information
	out << "---------------" << endl;
	out << card.name << endl;
	out << "Image source: " << card.image << endl;
	// Print ability/abilities
	out << "ABILITIES" << endl;
	for (int i = 0; i < card.abilityCount; i++) {
		out << card.abilities[i] << endl;
	}
	// Print action(s)
	out << "ACTIONS" << endl;
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
	out << "---------------" << endl;
	return out;
}

/*******
  ACTION
 *******/

 // Assignment operator
Action& Action::operator= (const Action& newAction) {
	// Check for self-assignment
	if (this == &newAction) {
		return *this;
	}

	action = newAction.action;
	actionValue = newAction.actionValue;

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

 // Assignment operator
Ability& Ability::operator= (const Ability& newAbility) {
	// Check for self-assignment
	if (this == &newAbility) {
		return *this;
	}

	type = newAbility.type;
	value = newAbility.value;
	setName = newAbility.setName;
	setTarget = newAbility.setTarget;
	countSetOnce = newAbility.countSetOnce;

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
		break;
	case eAbility_Immune:
		out << "Immune to Attack";
		break;
	case eAbility_None:
		out << "No Ability";
		break;
	}
	return out;
}
