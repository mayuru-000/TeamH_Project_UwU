#pragma once
#include "../Library/GameObject.h"

class Common :public GameObject
{
public:
	Common();
	~Common();

	int weponNum;

	int nowStage;

	int Score;
	int hiScore;
};