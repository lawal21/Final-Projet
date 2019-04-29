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
	x--;
}

void Location::MoveDown()
{
	y++;
}
void Location::MoveUp()
{
	y--;
}

void Location::MoveRight(int amount)
{
	for (int i = 0; i < amount; i++) {
		x++;
	}
}

void Location::MoveLeft(int amount)
{
	for (int i = 0; i < amount; i++) {
		x--;
	}
}

void Location::MoveDown(int amount)
{
	for (int i = 0; i < amount; i++) {
		y++;
	}
}
void Location::MoveUp(int amount)
{
	for (int i = 0; i < amount; i++) {
		y--;
	}
}

float Location::GetX() {
	return x;
}

float Location::GetY() {
	return y;
}