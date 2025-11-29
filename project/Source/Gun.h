#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "../Library/GameObject.h"

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
	int Maxammo = 8;
	int ammoDamage;

	int startTime;
	int shotedSpan;

	float deg = 0.0;
	float rad = 0.0;
	float Expansion = 0.05;
	float ExpansionRate = 0.03;

	bool reroading = FALSE;
	bool shotcool = TRUE;
};
