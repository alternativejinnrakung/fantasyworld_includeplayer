#include "Orc.hpp"


Orc::Orc()
{
}


Orc::~Orc()
{
}

int Orc::getHP() {
	return rand() % 29 + 50;
}

int Orc::getATK() {
	return rand() % 5 + 6;
}

std::string Orc::getType() {
	return "orc";
}