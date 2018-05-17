#pragma once
#include<iostream>

class Orc
{
	int orc_hp;

public:
	Orc();
	~Orc();
	int getHP();
	int getATK();
	std::string getType();
};

