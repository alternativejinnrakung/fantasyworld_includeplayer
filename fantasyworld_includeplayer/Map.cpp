#include "Map.hpp"

Map::Map()
{
	assert(MAP_WIDTH * MAP_HEIGHT > MONS_AMOUNT);

	worldmap.resize(MAP_WIDTH, std::vector<int>(MAP_HEIGHT));
	playermap.resize(MAP_WIDTH, std::vector<int>(MAP_HEIGHT));

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
	SpawnMonster<std::vector<std::shared_ptr<Monster>>> mons(monsters);
	monsters = mons.push_obj();
	getchar();
	for (int i = 0; i < MONS_AMOUNT; i++) {
		monsters.push_back(std::make_shared<Monster>());
	}
	player = std::make_shared<Player>();
}

void Map::createWorld() {
	for (int i = 0; i < MONS_AMOUNT; i++) {
		monsters[i]->setLocation(worldmap);
		worldmap[monsters[i]->getLocX()][monsters[i]->getLocY()] = monsters[i]->getHealth();
	}
}

void Map::drawMap() {
	for (int i = 0; i < 10 / 3; i++) {
		std::cout << std::endl << std::endl << std::endl << std::endl;
	}
	std::cout << static_cast<char>(TOPLEFT_MAP);
	for (int i = 0; i < MAP_WIDTH - 1; i++) {
		std::cout << static_cast<char>(MID_MAP) << static_cast<char>(MID_MAP) << static_cast<char>(TOPMID_MAP);
	}
	std::cout << static_cast<char>(MID_MAP) << static_cast<char>(MID_MAP) << static_cast<char>(TOPRIGHT_MAP) << std::endl;
	for (int j = 0; j < MAP_HEIGHT; j++) {
		std::cout << static_cast<char>(SPLITTER);
		for (int i = 0; i < MAP_WIDTH; i++) {
			if (playermap[i][j] > 0) {
				std::cout << "H";
			}
			else {
				std::cout << "-";
			}
			if (worldmap[i][j] > 0) {
				std::cout << "M";
			}
			else {
				std::cout << "-";
			}
			std::cout << static_cast<char>(SPLITTER);
		}
		std::cout << std::endl;
	}
	std::cout << static_cast<char>(BOTLEFT_MAP);
	for (int i = 0; i < MAP_WIDTH - 1; i++) {
		std::cout << static_cast<char>(MID_MAP) << static_cast<char>(MID_MAP) << static_cast<char>(BOTMID_MAP);
	}
	std::cout << static_cast<char>(MID_MAP) << static_cast<char>(MID_MAP) << static_cast<char>(BOTRIGHT_MAP) << std::endl;
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
			std::cout << "Player fight with a monster" << std::endl;
			std::cout << "Monster: " << monsters[i]->getHealth() << " - " << player->getAtk() << " = ";
			monsters[i]->reduceHP(player->getAtk());
			std::cout << monsters[i]->getHealth() << std::endl;
			std::cout << "Player: " << player->getHP() << " - " << monsters[i]->getHealth() << " = ";
			gameover = player->receivedDamage(monsters[i]->getAtk());
			std::cout << player->getHP() << std::endl;
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
		diff = (static_cast<float>(t2) - static_cast<float>(t1)) / CLOCKS_PER_SEC;
		if (diff > 0.0) {
			t1 = clock();
			this->updateMap();
		}
		if (gameover) {
			std::cout << std::endl << "Game Over";
			setInput();
			break;
		}
	}
}

char Map::setInput() {
	return static_cast<char>(_getche());
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