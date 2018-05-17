#include "Zombie.hpp"



Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}

int Zombie::getHP() {
	return rand() % 29 + 5;
}

int Zombie::getATK() {
	return rand() % 5 + 1;
}

std::string Zombie::getType() {
	return "zombie";
}