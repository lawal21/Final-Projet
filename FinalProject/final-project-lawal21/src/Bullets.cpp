#include "Bullets.h"

Bullets::Bullets(bool isEnemy)
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
