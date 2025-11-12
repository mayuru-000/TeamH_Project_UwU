#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "Gun.h"
#include "../Library/GameObject.h"

class Player : public GameObject
{
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;

	void ChangeGun(int gunnum);

private:
	Gun* gun = NULL;

	int gunmode = 1;
	int gunflag = 1;

};
