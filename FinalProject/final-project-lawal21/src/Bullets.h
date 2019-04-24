#pragma once

#include "Location.h"
#include "ofMain.h"

class Bullets
{
public:
	ofImage Bullet;
	Bullets(bool isEnemy);
	~Bullets();
	Location locationTL;
	Location locationBR;
private:
	int bulletHeight;
	int bulletWidth = 1;
};

