#pragma once
#include "../Library/GameObject.h"

class Target :public GameObject
{
public:
	Target();
	Target(int fx, int fy, int handle, int fhp, int speed);
	~Target();
	void Update() override;
	void Draw() override;

	bool isHit(int px, int py, int r[], int dmg[], int num);
private:
	int nam;
	int tImage;
	int bmImage;
	int tWIDTH, tHEIGHT;

	int hp, maxhp;
	int hit;
	int x, y;
	int dx, dy;
	int scrollX;
	int deadCounter;

	bool breaked;
};
