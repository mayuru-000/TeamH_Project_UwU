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
	int mod[10] = { 9,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
};