#include "Location.h"

Location::Location()
{
}

Location::Location(float newX, float newY)
{
	x = newX;
	y = newY;
}

void Location::SetX(float newX) 
{
	x = newX;

}
void Location::SetY(float newY)
{
	y = newY;

}

void Location::MoveRight()
{
	x++;
}
void Location::MoveLeft()
{
	x--
};
void Location::MoveDown()
{
	y++;
}
void Location::MoveUp()
{
	y--
};
};