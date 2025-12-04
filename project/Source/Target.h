#pragma once
#include "../Library/GameObject.h"

class Target :public GameObject
{
public:
	Target();
	Target(int fx, int fy, int handle, int speed);
	~Target();
	void Update() override;
	void Draw() override;

	bool isHit(int px, int py, int r[], int dmg[], int num);
private:
	int tImage;
	int tWIDTH, tHEIGHT;

	int hp;
	int x, y;
	int dx, dy;
	int scrollX;
	int hitDmg;

	bool kill = FALSE;
};
