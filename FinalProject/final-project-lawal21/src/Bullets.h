#pragma once

#include "Location.h"
#include "ofMain.h"
#include "Players.h"
#include "Monsters.h"

class Bullets
{
public:
	ofImage Bullet;
	Bullets(bool isEnemy);
	~Bullets();
	Location locationTL;
	Location locationBR;
private:
	bool MonsterCollision(Monsters monster);
	bool PlayerCollision(Players player);
	bool PixelWithinBounds(Location pixel, Location tlBound, Location brBound);
	int bulletHeight;
	int bulletWidth = 1;
};

