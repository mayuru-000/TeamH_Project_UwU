#pragma once

#include "Gun.h"
#include "Assault.h"
#include "../Library/GameObject.h"

class Gunsetting:public GameObject
{
public:
	Gunsetting();
	~Gunsetting();

private:
	Gun* gun = NULL;
	Assault* assault = NULL;
};
