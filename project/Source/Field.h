#pragma once
#include "../Library/GameObject.h"

#include "Gun.h"
#include "Assault.h"

class Field : public GameObject
{
public:
	Field();
	~Field();
	void Update() override;
	void Draw() override;

private:
	/*Gun* gun = NULL;
	Assault* assault = NULL;*/

	int fImage;
	int bgImage;

	int fImageX, fImageY;
	int ImageX, ImageY;

	int goalline;

	int hp;
	int score;
	int scrollX;
	int speedX;
	int x, y;
	int dx, dy;

	bool cleared;
};