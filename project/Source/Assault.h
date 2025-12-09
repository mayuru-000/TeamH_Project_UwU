#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "../Library/GameObject.h"

class Assault : public GameObject
{
public:
	Assault();
	~Assault();
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
	int ammo;

	int count;
	int startTime;

	float deg;
	float rad;
	float Expansion;

	bool reroading = FALSE;
	bool shotcool = TRUE;

	const int Maxammo = 30;
	const float ExpansionRate = 0.00025;

	static const int num = 3;
	int range[num] = { 10,30,50 };
	int ammoDamage[num] = { 50,20,5 };
};
