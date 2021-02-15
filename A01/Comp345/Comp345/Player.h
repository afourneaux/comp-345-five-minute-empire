#pragma once
#include <iostream>
#include <vector>
#include "Map.h"
#include "Card.h"
#include <iostream>
using namespace std;
	struct Cube {
		Territory location;
		bool isPlaced = false;
	};
	struct Disk {
		Territory location;
		bool isBuilt = false;
	};
	struct BidingFacility {
		Territory location;
	};
	struct Player{
	public:
		Player(string lastName);
		~Player();
		void PayCoin(int amt);
		void PlaceNewArmies(Cube* src, Territory* dest);
		void MoveArmies(Cube* src, Territory* dest);
		void MoveOverLand(Cube* src, Territory* dest);
		void BuildCity(Territory* dest);
		void DestroyArmy(Cube* friendly, Cube* ennemie);
		void InitializePlayer();

	private:
		vector<Territory*> territories;
		vector<Cube*> cubes;
		vector<Disk*> disks;;
		vector <Card*> hand;
		BidingFacility* bf;
		int total_coin = 14;
		string lastName = "";
	};


	