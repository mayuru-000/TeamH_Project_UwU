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

	float Deg2Rad(int dg) { return dg * (M_PI / 180.0); }

private:
	int gunImage;

	int x = 0;
	int y = 0;
	int ammo = 0;

	float deg = 0.0;
	float rad = 0.0;
	float Expansion = 0.1;
	float ExpansionRate = 0.0005;
};
