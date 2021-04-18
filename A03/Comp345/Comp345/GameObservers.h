#pragma once
#include <list>


using namespace std;
class Game;

class Observer {
public:
	Observer();
	~Observer();
	virtual void Update() = 0;
};

class Subject {
public:
	void Attach(Observer *obs);
	void Detach(Observer *obs);
	void Notify();
	Subject();
	~Subject();
private:
	list<Observer*> *observers;
};

class GameStateView : public Observer {
public:
	GameStateView();
	GameStateView(Game* game);
	~GameStateView();
	void Update();
	void Display();
private:
	const int MAP_COLUMN_WIDTH = 10;
	const int STATS_COLUMN_WIDTH = 15;
	const int STATS_COLUMN_COUNT = 10;
	const int CARD_WIDTH = 25;
	Game* game;
};

class PlayerStateView : public Observer {
public:
	PlayerStateView();
	PlayerStateView(Game* game);
	~PlayerStateView();
	void Update();
	void Display();
private:
	Game* game;
};