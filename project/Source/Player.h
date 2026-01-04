#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "Gun.h"
#include "Assault.h"
#include "Granade.h"
#include "../Library/GameObject.h"

class Player : public GameObject
{
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;

private:
	Gun* gun = NULL;
	Assault* assault = NULL;

	int bufImage;
	int carImage;
	int roadImage;

	int carWIDTH, carHEIGHT;
	int roadWIDTH, roadHEIGHT;

	int nowSelect;
	int scrollX;
	int bufSize;
	int count;
	int flameCounter;

	bool prevPush;
};
