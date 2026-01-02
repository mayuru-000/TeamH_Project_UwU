#pragma once
#include <string>
#include "../Library/GameObject.h"

using namespace std;

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

	int score;
	int hiScore;
	int mod[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
	//int mod[10] = { 0,1,2,3,4,5,-1,-1,-1,-1 };
};