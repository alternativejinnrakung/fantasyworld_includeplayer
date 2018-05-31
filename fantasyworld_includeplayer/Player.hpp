#pragma once
#include<iostream>

class Player
{
private:
	int health;
	int atk;
	int locX, locY;
public:
	Player();
	virtual ~Player();
	void setLocation(int x, int y);
	bool receivedDamage(int damage);
	int getHP();
	int getAtk();
	int getLocX();
	int getLocY();
};