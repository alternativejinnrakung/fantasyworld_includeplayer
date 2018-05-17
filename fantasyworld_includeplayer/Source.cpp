#include "Map.hpp"

#define _CRTDBG_MAP_ALOC

char setInput() {
	return _getche();
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(time(NULL));
	Map *map = new Map();
	delete map;
	return 0;
}