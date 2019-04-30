#include "Players.h"

Players::Players()
{
	ofLoadImage(Player, "Player.png");
	Player.resize(kPlayerWidth, kPlayerHeight);
}
