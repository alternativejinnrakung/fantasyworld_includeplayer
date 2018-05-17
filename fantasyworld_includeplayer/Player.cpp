#include "Player.hpp"

Player::Player()
{
	health = rand() % 25 + 75;
	atk = rand() % 10 + 15;
}


Player::~Player()
{
}

void Player::setLocation(int x, int y) {
	locX = x;
	locY = y;
}

bool Player::receivedDamage(int damage) {
	health -= damage;
	if (health < 0) {
		health = 0;
		return true;
	}
	return false;
}

int Player::getHP() {
	return health;
}

int Player::getAtk() {
	return atk;
}

int Player::getLocX() {
	return locX;
}

int Player::getLocY() {
	return locY;
}