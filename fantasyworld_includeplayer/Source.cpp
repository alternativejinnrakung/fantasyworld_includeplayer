#include "Map.hpp"

#define _CRTDBG_MAP_ALOC

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(static_cast<unsigned int>(time(nullptr)));

	Map *map = new Map();
	delete map;
	return 0;
}