#include "Player.h"
#include<iostream>
using namespace std;

Player::Player(string last_Name)
{
	InitializePlayer();
	this->lastName = last_Name;
	this->bf = new BidingFacility();
}
Player::~Player(){}

void Player::PayCoin(int amt) {
	this->total_coin -= amt;
}
void Player::PlaceNewArmies(Cube* army, Territory* dest) {
	army->location = *dest;
	army->isPlaced = true;
}
void Player::MoveArmies(Cube* army, Territory* dest) {
	army->location = *dest;
}
void Player::MoveOverLand(Cube* army, Territory* dest) {
	army->location = *dest;
}
void Player::BuildCity(Territory* dest) {
	for (int i = 0; i < 3; i++)
		if (!disks[i] -> isBuilt)
			disks[i]->location = *dest;
}
void Player::DestroyArmy(Cube* friendly, Cube* ennemie) {
	ennemie->isPlaced = false;
}
void Player::InitializePlayer() {
	for (int i = 0; i < 18; i++) 
		this->cubes.push_back(new Cube());
	for (int j = 0; j < 3; j++)
		this->disks.push_back(new Disk());
	for (int v = 0; v < 3; v++)
		this->hand.push_back(new Card());
}
int testPlayer();


