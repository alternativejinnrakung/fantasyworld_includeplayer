#include "Map.hpp"

Map::Map()
{
	assert(MAP_WIDTH * MAP_HEIGHT > MONS_AMOUNT);

	worldmap.resize(MAP_WIDTH, vector<int>(MAP_HEIGHT));
	playermap.resize(MAP_WIDTH, vector<int>(MAP_HEIGHT));

	for (int j = 0; j < MAP_HEIGHT; j++) {
		for (int i = 0; i < MAP_WIDTH; i++) {
			worldmap[i][j] = 0;
			playermap[i][j] = 0;
		}
	}
	this->monster_initiation();
	player->setLocation(MAP_WIDTH / 2, MAP_HEIGHT / 2);
	playermap[player->getLocX()][player->getLocY()] = player->getHP();
	this->createWorld();
	this->drawMap();
	this->summon_world_clock();
}

Map::~Map()
{
}

void Map::monster_initiation() {
	for (int i = 0; i < MONS_AMOUNT; i++) {
		monsters.push_back(make_shared<Monster>());
	}
	player = make_shared<Player>();
}

void Map::createWorld() {
	for (int i = 0; i < MONS_AMOUNT; i++) {
		monsters[i]->setLocation(worldmap);
		worldmap[monsters[i]->getLocX()][monsters[i]->getLocY()] = monsters[i]->getHealth();
	}
}

void Map::drawMap() {
	for (int i = 0; i < 10 / 3; i++) {
		cout << endl << endl << endl << endl;
	}
	cout << static_cast<char>(TOPLEFT_MAP);
	for (int i = 0; i < MAP_WIDTH - 1; i++) {
		cout << static_cast<char>(MID_MAP) << static_cast<char>(MID_MAP) << static_cast<char>(TOPMID_MAP);
	}
	cout << static_cast<char>(MID_MAP) << static_cast<char>(MID_MAP) << static_cast<char>(TOPRIGHT_MAP) << endl;
	for (int j = 0; j < MAP_HEIGHT; j++) {
		cout << static_cast<char>(SPLITTER);
		for (int i = 0; i < MAP_WIDTH; i++) {
			if (playermap[i][j] > 0) {
				cout << "H";
			}
			else {
				cout << "-";
			}
			if (worldmap[i][j] > 0) {
				cout << "M";
			}
			else {
				cout << "-";
			}
			cout << static_cast<char>(SPLITTER);
		}
		cout << endl;
	}
	cout << static_cast<char>(BOTLEFT_MAP);
	for (int i = 0; i < MAP_WIDTH - 1; i++) {
		cout << static_cast<char>(MID_MAP) << static_cast<char>(MID_MAP) << static_cast<char>(BOTMID_MAP);
	}
	cout << static_cast<char>(MID_MAP) << static_cast<char>(MID_MAP) << static_cast<char>(BOTRIGHT_MAP) << endl;
}

void Map::updateMap() {
	input = this->setInput();
	this->activeInput();
	for (int i = 0; i < MONS_AMOUNT; i++) {
		if (monsters[i]->getHealth() == 0) {
			worldmap[monsters[i]->getLocX()][monsters[i]->getLocY()] = 0;
			monsters[i]->setHP();
			monsters[i]->setLocation(worldmap);
		}
		worldmap[monsters[i]->getLocX()][monsters[i]->getLocY()] = monsters[i]->getHealth();
	}
	drawMap();
	for (int i = 0; i < MONS_AMOUNT; i++) {
		if (monsters[i]->getLocX() == player->getLocX() && monsters[i]->getLocY() == player->getLocY()) {
			cout << "Player fight with a monster" << endl;
			cout << "Monster: " << monsters[i]->getHealth() << " - " << player->getAtk() << " = ";
			monsters[i]->reduceHP(player->getAtk());
			cout << monsters[i]->getHealth() << endl;
			cout << "Player: " << player->getHP() << " - " << monsters[i]->getHealth() << " = ";
			gameover = player->receivedDamage(monsters[i]->getAtk());
			cout << player->getHP() << endl;
		}
	}
	input = 0;
}

void Map::summon_world_clock() {
	clock_t t1, t2;
	float diff;
	t1 = clock();
	while (true) {
		t2 = clock();
		diff = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
		if (diff > 1.0) {
			t1 = clock();
			this->updateMap();
		}
		if (gameover) {
			cout << endl << "Game Over";
			setInput();
			break;
		}
	}
}

char Map::setInput() {
	return _getche();
}

void Map::activeInput() {
	playermap[player->getLocX()][player->getLocY()] = 0;
	if (input == 'a') {
		if (player->getLocX() > 0) {
			player->setLocation(player->getLocX() - 1, player->getLocY());
		}
	}
	else if (input == 'w') {
		if (player->getLocY() > 0) {
			player->setLocation(player->getLocX(), player->getLocY() - 1);
		}
	}
	else if (input == 'd') {
		if (player->getLocX() < MAP_WIDTH - 1) {
			player->setLocation(player->getLocX() + 1, player->getLocY());
		}
	}
	else if (input == 's') {
		if (player->getLocX() < MAP_HEIGHT - 1) {
			player->setLocation(player->getLocX(), player->getLocY() + 1);
		}
	}
	playermap[player->getLocX()][player->getLocY()] = player->getHP();
}