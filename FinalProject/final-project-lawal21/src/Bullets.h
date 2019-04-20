#pragma once

#include "Location.h"
#include "ofMain.h"

class Bullets
{
public:
	ofImage Bullet;
	Bullets();
	~Bullets();
	bool isEnemy;
	Location locationTL;
	Location locationBR;
private:
	int bulletHeight;
	int bulletWidth = 1;
};

