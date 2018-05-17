#pragma once
#include<iostream>

class Zombie
{
private:
	int zombie_hp;
public:
	Zombie();
	~Zombie();
	int getHP();
	int getATK();
	std::string getType();
};

