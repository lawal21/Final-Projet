#pragma once

#include "Location.h"
#include "ofMain.h"

class Players
{
public:
	ofImage Player;
	Players();
	~Players();
	Location LocationTopLeft;
	Location LocationBottomRight;
private:
	const int kPlayerHeight = 24;
	const int kPlayerWidth = 32;
};

