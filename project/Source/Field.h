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

	void addSpanA(int x) { objSpan_A = x; sponed_A = FALSE; }
	void addSpanB(int x) { objSpan_B = x; sponed_B = FALSE; }

	bool cleared;
private:
	int fImage;
	int bgImage;

	int fImageX, fImageY;
	int ImageX, ImageY;

	int goalline;

	int hp;
	int mapX;
	int scrollX;
	int dx, dy;
	int objSpan_A, objSpan_B;
	int objSponePoint_A, objSponePoint_B;
	const int blank = 1000;

	bool sponed_A, sponed_B;
};