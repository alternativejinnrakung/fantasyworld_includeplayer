#include "Monster.hpp"

Monster::Monster()
{
	setHP();
}


Monster::~Monster()
{
}

void Monster::reduceHP(int damage) {
	REQUIRE(health >= 0); //validate input
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}

void Monster::setHP() {
	int type = rand() % 2 + 1;
	if (type == 1) {
		Zombie *zom = new Zombie();
		health = zom->getHP();
		attack = zom->getATK();
		mons_type = zom->getType();
		delete zom;
	}
	else if (type == 2) {
		Orc *orc = new Orc();
		health = orc->getHP();
		attack = orc->getATK();
		mons_type = orc->getType();
		delete orc;
	}
	PROMISE(health >= 0); //validate output

}

void Monster::setLocation(const std::vector<std::vector<int>> worldmap) {
	while (true) {
		locX = rand() % 30;
		locY = rand() % 30;
		if (worldmap[locX][locY] == 0) {
			break;
		}
	}
}

int Monster::getLocX() {
	return locX;
}

int Monster::getLocY() {
	return locY;
}

int Monster::getHealth() {
	return health;
}

int Monster::getAtk() {
	return attack;
}