#include "Cards.h"
#include <iostream>
#include <algorithm>

/*******
  DECK
 *******/


// constructor
Deck::Deck(int num_player) {
	deckIndex = 0;
	CalcSize( num_player);
	Generate();
	
	setShuffel(Shuffel , num_player);

}

// Copy constructor
Deck::Deck(const Deck* deck) {
	deckIndex = deck->deckIndex;
	cards = new Card[size];

	for (int i = 0; i < size; i++) {
		cards[i] = deck->cards[i];
	}
}

Deck::~Deck() {
	delete[] cards;
}

void Deck::CalcSize(int num_player)
{
	size = 25;
	if (num_player == 4)
	{
		size = 31;

	}
	if (num_player == 3)
	{
		size = 29;

	}

}

int Deck::getSize()
{
	return size;
}

// Create the deck and populate it with hardcoded card data
void Deck::Generate()
{
//fix

	int index = -1;


	cards = new Card[size];

	 index++;
	// index 0
	cards[index].name = "Dire Dragon";
	cards[index].image = "card_dire_dragon.png";
	cards[index].actionChoice = eChoice_And;
	cards[index].actionCount = 2;
	cards[index].abilityCount = 1;
	cards[index].abilities = new Ability[1];
	cards[index].actions = new Action[2];
	cards[index].abilities[0].type = eAbility_Flying;
	cards[index].actions[0].action = eAction_PlaceArmies;
	cards[index].actions[0].actionValue = 3;
	cards[index].actions[1].action = eAction_DestroyArmies;
	cards[index].actions[1].actionValue = 1;

	index++;
	// index 1
	cards[index].name = "Dire Eye";
	cards[index].image = "card_dire_eye.png";
	cards[index].actionCount = 1;
	cards[index].abilityCount = 1;
	cards[index].abilities = new Ability[1];
	cards[index].actions = new Action[1];
	cards[index].abilities[0].type = eAbility_Flying;
	cards[index].actions[0].action = eAction_PlaceArmies;
	cards[index].actions[0].actionValue = 4;

	index++;
	// index 2
	cards[index].name = "Dire Goblin";
	cards[index].image = "card_dire_goblin.png";
	cards[index].actionCount = 1;
	cards[index].abilityCount = 1;
	cards[index].abilities = new Ability[1];
	cards[index].actions = new Action[1];
	cards[index].abilities[0].type = eAbility_Elixir;
	cards[index].abilities[0].value = 1;
	cards[index].actions[0].action = eAction_MoveArmies;
	cards[index].actions[0].actionValue = 5;

	index++;
	// index 3
	cards[index].name = "Dire Ogre";
	cards[index].image = "card_dire_ogre.png";
	cards[index].actionCount = 1;
	cards[index].abilityCount = 1;
	cards[index].abilities = new Ability[1];
	cards[index].actions = new Action[1];
	cards[index].abilities[0].type = eAbility_VpPerCoins;
	cards[index].abilities[0].value = 1;
	cards[index].abilities[0].setTarget = 3;
	cards[index].actions[0].action = eAction_MoveArmies;
	cards[index].actions[0].actionValue = 2;

	index++;
	// index 4
	cards[index].name = "Lake";
	cards[index].image = "card_lake.png";
	cards[index].actionCount = 2;
	cards[index].actionChoice = eChoice_Or;
	cards[index].abilityCount = 1;
	cards[index].abilities = new Ability[1];
	cards[index].actions = new Action[2];
	cards[index].abilities[0].type = eAbility_VpPerCardName;
	cards[index].abilities[0].value = 1;
	cards[index].abilities[0].setTarget = 1;
	cards[index].abilities[0].setName = "Forest";
	cards[index].abilities[0].countSetOnce = false;
	cards[index].actions[0].action = eAction_PlaceArmies;
	cards[index].actions[0].actionValue = 2;
	cards[index].actions[1].action = eAction_MoveArmies;
	cards[index].actions[1].actionValue = 3;

	index++;
	// index 5
	cards[index].name = "Forest Elf";
	cards[index].image = "card_forest_elf.png";
	cards[index].actionCount = 2;
	cards[index].actionChoice = eChoice_Or;
	cards[index].abilityCount = 1;
	cards[index].abilities = new Ability[1];
	cards[index].actions = new Action[2];
	cards[index].abilities[0].type = eAbility_PlusOneArmy;
	cards[index].actions[0].action = eAction_PlaceArmies;
	cards[index].actions[0].actionValue = 3;
	cards[index].actions[1].action = eAction_MoveArmies;
	cards[index].actions[1].actionValue = 2;

	index++;
	// index 6
	cards[index].name = "Forest Gnome";
	cards[index].image = "card_forest_gnome.png";
	cards[index].actionCount = 1;
	cards[index].abilityCount = 1;
	cards[index].abilities = new Ability[1];
	cards[index].actions = new Action[1];
	cards[index].abilities[0].type = eAbility_Elixir;
	cards[index].abilities[0].value = 3;
	cards[index].actions[0].action = eAction_MoveArmies;
	cards[index].actions[0].actionValue = 2;

	index++;
	// index 7
	cards[index].name = "Forest Tree Town";
	cards[index].image = "card_forest_tree_town.png";
	cards[index].actionCount = 1;
	cards[index].abilityCount = 1;
	cards[index].abilities = new Ability[1];
	cards[index].actions = new Action[1];
	cards[index].abilities[0].type = eAbility_PlusOneMove;
	cards[index].actions[0].action = eAction_BuildCity;

	index++;
	// index 8
	cards[index].name = "Graveyard";
	cards[index].image = "card_graveyard.png";
	cards[index].actionCount = 1;
	cards[index].abilityCount = 1;
	cards[index].abilities = new Ability[1];
	cards[index].actions = new Action[1];
	cards[index].abilities[0].type = eAbility_VpPerCardName;
	cards[index].abilities[0].value = 1;
	cards[index].abilities[0].setTarget = 1;
	cards[index].abilities[0].setName = "Cursed";
	cards[index].abilities[0].countSetOnce = false;
	cards[index].actions[0].action = eAction_BuildCity;

	
	index++;
	// index 9
	cards[index].name = "Noble Hills";

	index++;
	// index 10
	cards[index].name = "Noble Knight";

	index++;
	// index 11
	cards[index].name = "Noble Unicorn";

	index++;
	// index 12
	cards[index].name = "Night Hydra";

	index++;
	// index 13
	cards[index].name = "Night Village";

	index++;
	// index 14
	cards[index].name = "Forest Pixie";

	index++;
	// index 15
	cards[index].name = "Stronghold";


	index++;
	// index 16
	cards[index].name = "Ancient Phoenix";

	index++;
	// index 17
	cards[index].name = "Ancient Tree Spirit";

	index++;
	// index 18
	cards[index].name = "Ancient Woods";

	index++;
	// index 19
	cards[index].name = "Ancient Sage";


	index++;
	// index 20
	cards[index].name = "Cursed Banshee";

	index++;
	// index 21
	cards[index].name = "Cursed Gargoyles";

	index++;
	// index 22
	cards[index].name = "Cursed King";

	index++;
	// index 23
	cards[index].name = "Cursed Mausolum";

	index++;
	// index 24
	cards[index].name = "Cursed Tower";

	if (size > 25)
	{

		index++;
		// index 25
		cards[index].name = "Mountain Dwarf";
		cards[index].image = "card_mountain_dwarf.png";
		cards[index].actionChoice = eChoice_And;
		cards[index].actionCount = 2;
		cards[index].abilityCount = 1;
		cards[index].abilities = new Ability[1];
		cards[index].actions = new Action[2];
		cards[index].abilities[0].type = eAbility_VpPerCardName;
		cards[index].abilities[0].value = 3;
		cards[index].abilities[0].setTarget = 2;
		cards[index].abilities[0].setName = "Mountain";
		cards[index].abilities[0].countSetOnce = true;
		cards[index].actions[0].action = eAction_PlaceArmies;
		cards[index].actions[0].actionValue = 2;
		cards[index].actions[1].action = eAction_DestroyArmies;
		cards[index].actions[1].actionValue = 1;


		
		index++;
		// index 26
		cards[index].name = "Mountain Treasury";
		cards[index].image = "card_mountain_treasury.png";
		cards[index].actionCount = 1;
		cards[index].abilityCount = 2;
		cards[index].abilities = new Ability[2];
		cards[index].actions = new Action[1];
		cards[index].abilities[0].type = eAbility_Elixir;
		cards[index].abilities[0].value = 1;
		cards[index].abilities[1].type = eAbility_Coins;
		cards[index].abilities[1].value = 2;
		cards[index].actions[0].action = eAction_MoveArmies;
		cards[index].actions[0].actionValue = 3;

		index++;
		// index 27
		cards[index].name = "Arcane Sphinx";

		index++;
		// index 28
		cards[index].name = "Arcane Temple";
	}
	if (size > 29)
	{
		index++;
		// index 29
		cards[index].name = "Castle";
		//cards[index].image = "";
		cards[index].actionCount = 1;
		cards[index].abilityCount = 1;
		cards[index].abilities = new Ability[1];
		cards[index].actions = new Action[2];
		cards[index].abilities[0].type = eAbility_Elixir;
		cards[index].abilities[0].value = 1;

		cards[index].actions[0].action = eAction_MoveArmies;
		cards[index].actions[0].actionValue = 3;
		cards[index].actions[1].action = eAction_BuildCity;


		index++;
		// index 30 ************
		cards[index].name = "Castle2";
		//cards[index].image = "";
		cards[index].actionCount = 1;
		cards[index].abilityCount = 1;
		cards[index].abilities = new Ability[1];
		cards[index].actions = new Action[2];
		cards[index].abilities[0].type = eAbility_Elixir;
		cards[index].abilities[0].value = 1;

		cards[index].actions[0].action = eAction_MoveArmies;
		cards[index].actions[0].actionValue = 3;
		cards[index].actions[1].action = eAction_BuildCity;

	}
	
}

// Retrieve the top card and remove it from the deck
Card* Deck::Draw()
{
	// If the deck is empty, return a null pointer
	if (deckIndex == size) {
		cout << "ERROR: Deck::Draw attempting to draw a card from an empty deck" << endl;
		return nullptr;
	}
	//Reading the index of cards from Shuffel[] by going through its indexes
	return &cards[Shuffel[(deckIndex++)]];
}

//shuffelling the data member, Shuffel[], that contains index of the cards
void Deck::setShuffel(int arrShuffel[] ,  int const num_player)
{

	//srand(time(NULL));

	 int* arr = new int[size];
	for (int a = 0; a < size ; a++)
	{
		arr[a] = a;
	}
	random_shuffle(arr, arr + size);
	Shuffel = arr;



}

// Assignment operator
Deck& Deck::operator= (const Deck& deck) {
	// Check for self-assignment
	if (this == &deck) {
		return *this;
	}

	deckIndex = deck.deckIndex;
	cards = new Card[size];

	for (int i = 0; i < size; i++) {
		cards[i] = new Card(deck.cards[i]);
	}

	return *this;
}

 //Stream insertion operator 
ostream& operator<<(ostream& out, const Deck& deck) {
	out << "Original deck size: " << deck.size << endl;
	out << "Total cards dealt: " << deck.deckIndex << endl;
	out << "Cards remaining in the deck: " << deck.size - deck.deckIndex << endl;
	out << "Card descriptions:" << endl;
	for (int i = deck.deckIndex; i < deck.size; i++) {
		out << deck.cards[i];
		out << endl;
	}
	return out;
}

/*******
  HAND
 *******/

// Default constructor
Hand::Hand(Deck* newDeck) {
	deck = newDeck;
	cards = new Card[HAND_SIZE];

	// Deal HAND_SIZE cards into the hand from the provided deck
	for (int i = 0; i < HAND_SIZE; i++) {
		cards[i] = deck->Draw();
	}
}

// Copy constructor
Hand::Hand(const Hand* hand) {
	deck = hand->deck; // Keep the assignment to the same deck
	cards = new Card[HAND_SIZE];
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
	int cost = GetCostAtIndex(index);
	Card* card = new Card(&cards[index]);
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
	return &cards[index];
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
	cards = new Card[HAND_SIZE];
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
	case eAbility_None:
		out << "No Ability";
		break;
	}
	return out;
}
