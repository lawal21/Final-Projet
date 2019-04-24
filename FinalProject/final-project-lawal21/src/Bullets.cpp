#include "Bullets.h"

Bullets::Bullets()
{
	if (isEnemy) {
		ofLoadImage(Bullet, "Enemy Bullet.png");
	}
	else {
		ofLoadImage(Bullet, "Player Bullet.png");
	}
}

Bullets::~Bullets()
{
}
