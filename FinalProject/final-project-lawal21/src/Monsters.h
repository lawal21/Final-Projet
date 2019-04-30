#pragma once

#include "Location.h"
#include "ofMain.h"

class Monsters
{
public:
	ofImage Monster;
	Monsters();	
	Monsters(int type);
	Location LocationTopLeft;
	Location LocationBottomRight;
	bool isAlive = true;
	Monsters& operator=(const Monsters& other);
private:
	const int kMonsterHeight = 40;
	const int kMonsterWidth = 40;
};

