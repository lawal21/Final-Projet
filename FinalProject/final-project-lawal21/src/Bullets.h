#pragma once

#include "Location.h"
#include "ofMain.h"
#include "Players.h"
#include "Monsters.h"

class Bullets
{
public:
	ofImage Bullet;
	Bullets();
	Bullets(bool is_enemy);
	Location LocationTopLeft;
	Location LocationBottomRight;
	bool enemy;
	bool isAlive = true;

private:
	int bullet_height;
	int bullet_width = 8;
};

