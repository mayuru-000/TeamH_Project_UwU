#pragma once
#include "../Library/GameObject.h"

class Target :public GameObject
{
public:
	Target();
	Target(int fx, int fy, int handle, int fhp, int speed, bool rast);
	~Target();
	void Update() override;
	void Draw() override;

	bool isHit(int px, int py, int r[], int dmg[], int num);
private:
	int tImage;
	int bmImage;
	int tWIDTH, tHEIGHT;

	int hp;
	int hit;
	int x, y;
	int scrollX;
	int deadCounter;

	bool rastobj;
	bool breaked;
};
