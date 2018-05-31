#pragma once
#include "Monster.hpp"

template<class T>
class SpawnMonster {
	T monsters_obj ;
public:
	SpawnMonster(T mons) {
		monsters_obj = mons;
	}
	T push_obj ();
};

template <class T>
T SpawnMonster<T>::push_obj() {
	T returnvalue = monsters_obj;
	std::cout << "yes";
	return returnvalue;
}

class Spawner
{
public:
	Spawner();
	virtual ~Spawner();
	virtual Monster *spawn() = 0;
};

