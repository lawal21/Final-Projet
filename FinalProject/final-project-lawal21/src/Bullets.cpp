#include "Bullets.h"

Bullets::Bullets()
{
	ofPixels *pixels;
	ofPixels pixel = ofPixels();

	if (isEnemy) {
		bulletHeight = 2;

		pixel.setColor(255, 0, 0);
		ofPixels pixel2 = ofPixels();
		pixel2.setColor(255, 0, 0);

		pixels[0] = pixel;
		pixels[1] = pixel2;

		Bullet.setFromPixels(pixels, bulletWidth, bulletHeight, OF_IMAGE_COLOR, true);
	}
	else {
		bulletHeight = 1;

		pixel.setColor(0, 0, 0);

		pixels[0] = pixel;

		Bullet.setFromPixels(pixels, bulletWidth, bulletHeight, OF_IMAGE_COLOR, true);
	}
}

Bullets::~Bullets()
{
}
