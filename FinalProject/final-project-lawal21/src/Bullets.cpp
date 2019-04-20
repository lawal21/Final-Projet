#include "Bullets.h"



Bullets::Bullets()
{
	if (isEnemy) {
		bulletHeight = 2;
	}
	else {
		bulletHeight = 1;
	}
}

Bullets::~Bullets()
{
}
