#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "Gun.h"
#include "Assault.h"
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
};
