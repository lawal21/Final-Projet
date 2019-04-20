#pragma once
class Bullets
{
public:
	Bullets();
	~Bullets();
	bool isEnemy;
	float locationx;
	float locationy;
private:
	int bulletHeight;
	int bulletWidth = 1;
};

