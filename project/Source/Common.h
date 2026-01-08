#pragma once
#include <string>
#include "../Library/GameObject.h"

using namespace std;

class Common :public GameObject
{
public:
	Common();
	int Speed(string mode);

	int weponNum;
	int nowStage;
	int speedX;

	int atkBuf;
	int gunrateBuf;
	int maxammoBuf;

	int score;
	int hiScore;

	int speedrange[10] = { 2,2,2,0,2 };
	int mod[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
};