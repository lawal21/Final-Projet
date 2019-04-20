#pragma once

#include "Location.h"
#include "ofMain.h"

class Monsters
{
public:
	ofImage Monster;
	Monsters(int type);
	~Monsters();
	Location locationTL;
	Location locationBR;	
private:
	const int kMonsterHeight = 10;
	const int kMonsterWidth = 10;
};

