#pragma once
#include "../Library/GameObject.h"


class Field : public GameObject
{
public:
	Field();
	~Field();
	void Update() override;
	void Draw() override;

private:
	int fImage;
	int bgImage;

	int fImageX, fImageY;
	int ImageX, ImageY;

	int goalline;

	int hp;
	int scrollX;
	int speedX;
	int x, y;
	int dx, dy;
};