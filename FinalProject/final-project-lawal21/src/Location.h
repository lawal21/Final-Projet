#pragma once
class Location
{
public:
	float GetX();
	float GetY();
	Location();
	Location(float newX, float newY);
	void SetX(float newX);
	void SetY(float newY);
	void MoveRight();
	void MoveLeft();
	void MoveDown();
	void MoveUp();
private:
	float x;
	float y;
};

