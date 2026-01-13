#pragma once
#include "../Library/GameObject.h"

class Ammo:public GameObject
{
public:
	Ammo();
	Ammo(int px, int py, float sp);
	~Ammo();
	void Update() override;
	void Draw() override;

private:
	int x, y;
	int dx, dy;
	int deltaX, deltaY;
	float speed;
	int ammoImage;
};
