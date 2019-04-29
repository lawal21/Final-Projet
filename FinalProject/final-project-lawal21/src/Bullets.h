#pragma once

#include "Location.h"
#include "ofMain.h"
#include "Players.h"
#include "Monsters.h"

class Bullets
{
public:
	ofImage Bullet;
	Bullets(bool is_enemy);
	Location LocationTopLeft;
	Location LocationBottomRight;
	bool enemy;
private:
	bool MonsterCollision(Monsters monster);
	bool PlayerCollision(Players player);
	bool PixelWithinBounds(Location pixel, Location tlBound, Location brBound);
	int bullet_height;
	int bullet_width = 1;
};

