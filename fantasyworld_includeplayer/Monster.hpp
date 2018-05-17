#pragma once
#include<iostream>
#include<ctime>
#include<assert.h>
#include<vector>

#include "Orc.hpp"
#include "Zombie.hpp"

#define REQUIRE(condition) assert(condition)
#define PROMISE(condition) assert(condition)
using namespace std;

class Monster
{
private:
	int health;
	int attack;
	int locX, locY;
	string mons_type;
public:
	Monster();
	virtual ~Monster();
	void setHP();
	void reduceHP(int damage);
	void setLocation(const vector<vector<int>> worldmap);
	int getLocX();
	int getLocY();
	int getHealth();
	int getAtk();
};