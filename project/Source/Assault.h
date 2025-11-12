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
	int weponSE;

	int reroaro, aroari;

	int x = 0;
	int y = 0;
	int count;
	int ammo;
	int Maxammo = 30;

	int startTime;

	float deg = 0.0;
	float rad = 0.0;
	float Expansion = 0.1;
	float ExpansionRate = 0.0005;

	bool reroading = FALSE;
	bool shotcool = TRUE;
};
