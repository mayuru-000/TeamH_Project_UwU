#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "../Library/GameObject.h"

const int Maxammo = 8;
const float ExpansionRate = 0.03;

class Gun : public GameObject
{
public:
	Gun();
	~Gun();
	void Update() override;
	void Draw() override;

	void Reroad();

	float Deg2Rad(int dg) { return dg * (M_PI / 180.0); }

private:
	int weponImage;
	int weponImage2;
	int weponSE;

	int reroaro, aroari;

	int x, y;
	int dx, dy;
	int ammo;

	int startTime;
	int shotedSpan;

	float deg;
	float rad;
	float Expansion;

	bool reroading = FALSE;
	bool shotcool = TRUE;
};
