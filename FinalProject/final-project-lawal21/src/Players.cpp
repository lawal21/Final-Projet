#include "Players.h"

Players::Players()
{
	ofLoadImage(Player, "Player.png");
	Player.resize(16, 4);
}


Players::~Players()
{
}
