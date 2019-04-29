#pragma once

#include "Location.h"
#include "ofMain.h"

class Monsters
{
public:
	ofImage Monster;
	Monsters();	
	Monsters(int type);
	~Monsters();
	Location LocationTopLeft;
	Location LocationBottomRight;
	bool isAlive = true;
	Monsters& operator=(const Monsters& other);
private:
	const int kMonsterHeight = 80;
	const int kMonsterWidth = 80;
};

