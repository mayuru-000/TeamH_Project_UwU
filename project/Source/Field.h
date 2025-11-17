#pragma once
#include "../Library/GameObject.h"


class Field : public GameObject
{
public:
	Field();
	~Field();
	void Update() override;
	void Draw() override;

	bool isHit(int px, int py, int dmg);
private:
	int fImage;

	int fImageX, fImageY;

	int hp;
	int x, y;
	int dx, dy;
};