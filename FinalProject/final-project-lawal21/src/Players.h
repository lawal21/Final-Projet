#pragma once

#include "Location.h"
#include "ofMain.h"

class Players
{
public:
	ofImage Player;
	Players();
	bool isAlive = true;
	int points = 0;
	Location LocationTopLeft;
	Location LocationBottomRight;
private:
	const int kPlayerHeight = 24;
	const int kPlayerWidth = 32;
};

