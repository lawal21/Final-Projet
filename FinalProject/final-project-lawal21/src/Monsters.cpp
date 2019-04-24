#include "Monsters.h"

Monsters::Monsters(int type)
{
	if (type == 1) {
		ofLoadImage(Monster, "Monster 1.png");
	}
	else if (type == 2) {
		ofLoadImage(Monster, "Monster 2.png");
	}
	else if (type == 3) {
		ofLoadImage(Monster, "Monster 3.png");
	}
	else if (type == 4) {
		ofLoadImage(Monster, "Monster 4.png");
	}
	else if (type == 5) {
		ofLoadImage(Monster, "Monster 5.png");
	}
}




Monsters::~Monsters()
{
}
