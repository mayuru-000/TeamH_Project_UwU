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

	void AddGunData(int nowAm, int maxAm) { nowAmmo = nowAm; maxAmmo = maxAm; }
private:
	Gun* gun = NULL;
	Assault* assault = NULL;

	int bufImage;
	int carImage;
	int roadImage;
	int uiImage;
	int carWIDTH, carHEIGHT;
	int roadWIDTH, roadHEIGHT;
	int txtWidth[100];

	int nowSelect;
	int scrollX;
	int bufSize;
	int count;
	int flameCounter;
	int nowAmmo, maxAmmo;

	bool prevPush;
};
