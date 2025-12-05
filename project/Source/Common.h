#pragma once
#include "../Library/GameObject.h"

class Common :public GameObject
{
public:
	Common();

	int weponNum;
	int nowStage;

	int Score;
	int hiScore;
	int mod[10] = { 0,1,2,0,0,0,-1,-1,-1,-1 };
};