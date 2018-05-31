#pragma once
#include<stdlib.h>
#include<crtdbg.h>
#include<conio.h>

#include<memory>
#include<vector>

#include "Player.hpp"
#include "Spawner.hpp"

class Map
{
private:
	const int MONS_AMOUNT = 100;
	const int MAP_WIDTH = 30;
	const int MAP_HEIGHT = 30;

	const int TOPLEFT_MAP = 201;
	const int TOPMID_MAP = 203;
	const int TOPRIGHT_MAP = 187;
	const int MID_MAP = 205;
	const int SPLITTER = 186;
	const int BOTLEFT_MAP = 200;
	const int BOTMID_MAP = 202;
	const int BOTRIGHT_MAP = 188;

	std::vector<std::vector<int>> worldmap;
	std::vector<std::vector<int>> playermap;
	std::vector<std::shared_ptr<Monster>> monsters;
	std::shared_ptr<Player> player;

	char input;
	bool gameover = false;
public:
	Map();
	virtual ~Map();

	void monster_initiation();
	void createWorld();
	void drawMap();
	void updateMap();
	void summon_world_clock();
	char setInput();
	void activeInput();
};

