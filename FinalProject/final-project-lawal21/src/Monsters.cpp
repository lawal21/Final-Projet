#include "Monsters.h"

Monsters::Monsters() {

}

Monsters::Monsters(int type)
{
	if (type == 1) {
		ofLoadImage(Monster, "Monster 1.png");
		ofLoadImage(Monster1, "Animate 1.png");
	}
	else if (type == 2) {
		ofLoadImage(Monster, "Monster 2.png");
		ofLoadImage(Monster1, "Animate 2.png");
	}
	else if (type == 3) {
		ofLoadImage(Monster, "Monster 3.png");
		ofLoadImage(Monster1, "Animate 3.png");
	}
	else if (type == 4) {
		ofLoadImage(Monster, "Monster 4.png");
		ofLoadImage(Monster1, "Animate 4.png");
	}
	else if (type == 5) {
		ofLoadImage(Monster, "Monster 5.png");
		ofLoadImage(Monster1, "Animate 5.png");
	}
	Monster.resize(kMonsterWidth, kMonsterHeight);
	Monster1.resize(kMonsterWidth, kMonsterHeight);
}

Monsters& Monsters::operator=(const Monsters& other) {
	Monster = other.Monster;
	Monster1 = other.Monster1;
	return *this;
}