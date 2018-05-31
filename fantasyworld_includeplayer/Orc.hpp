#pragma once
#include<iostream>

class Orc
{
	int orc_hp;

public:
	Orc();
	virtual ~Orc();
	int getHP();
	int getATK();
	std::string getType();
};

