#pragma once

#include "Gun.h"
#include "Assault.h"
#include "Granade.h"
#include "Launcher.h"
#include "../Library/GameObject.h"

class Gunsetting:public GameObject
{
public:
	Gunsetting();
	~Gunsetting();
private:
	Gun* gun = NULL;
	Assault* assault = NULL;
	Granade* granade = NULL;
	Launcher* launcher = NULL;

	//bufは割合(n％アップ)を少数で代入さす
	//グレの最大個数だけ整数値
	float atkBuf;		
	float rateBuf;
	float maxammoBuf;
	float bomAtkBuf;
	float bomRangeBuf;
	int   bomAmmoBuf;
};
