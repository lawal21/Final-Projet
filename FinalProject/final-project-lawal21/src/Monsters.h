#pragma once
class Monsters
{
public:
	Monsters();
	~Monsters();
	void MoveMonsters();
	float locationx;
	float locationy;
private:
	void CreateMonster(int type);
	const int kMonsterHeight = 10;
	const int kMonsterWidth = 10;
};

