#include "Bullets.h"

Bullets::Bullets() {

}

Bullets::Bullets(bool is_enemy)
{
	if (is_enemy) {
		ofLoadImage(Bullet, "Enemy Bullet.png");
		bullet_height = 16;
		enemy = is_enemy;
	}
	else {
		ofLoadImage(Bullet, "Player Bullet.png");
		bullet_height = 8;
		enemy = is_enemy;
	}
	Bullet.resize(bullet_width, bullet_height);
}
