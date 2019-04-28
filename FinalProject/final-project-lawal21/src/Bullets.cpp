#include "Bullets.h"

Bullets::Bullets(bool isEnemy)
{
	if (isEnemy) {
		ofLoadImage(Bullet, "Enemy Bullet.png");
		bulletHeight = 2;
	}
	else {
		ofLoadImage(Bullet, "Player Bullet.png");
		bulletHeight = 1;
	}
}

Bullets::~Bullets()
{

}

bool Bullets::MonsterCollision(Monsters monster) {
	if (PixelWithinBounds(locationTL, monster.locationTL, monster.locationBR) ||
		PixelWithinBounds(locationBR, monster.locationTL, monster.locationBR)) {
		return true;
	}
	return false;
}

bool Bullets::PlayerCollision(Players player) {
	if (PixelWithinBounds(locationTL, player.locationTL, player.locationBR)) {
		return true;
	}
	return false;
}

bool Bullets::PixelWithinBounds(Location pixel, Location tlBound, Location brBound) {
	if ((pixel.GetX() >= tlBound.GetX() && pixel.GetX <= brBound.GetX()) &&
		pixel.GetY() >= tlBound.GetY() && pixel.GetY <= brBound.GetY()) {
		return true;
	}
	return false;
}