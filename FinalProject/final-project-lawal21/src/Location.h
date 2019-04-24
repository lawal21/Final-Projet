#pragma once
class Location
{
public:
	float x;
	float y;
	Location();
	Location(float newX, float newY);
	void SetX(float newX);
	void SetY(float newY);
	void MoveRight();
	void MoveLeft();
	void MoveDown();
	void MoveUp();
};

