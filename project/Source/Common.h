#pragma once
#include "../Library/GameObject.h"

class Common :public GameObject
{
public:
	Common();

	int weponNum;
	int nowStage;
	int speedX;

	int atkBuf;
	int gunrateBuf;
	int maxammoBuf;

	int Score;
	int hiScore;
	//int mod[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
	int mod[10] = { 0,1,2,3,4,5,6,-1,-1,-1 };
};