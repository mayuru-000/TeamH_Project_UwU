#pragma once
#include <string>
#include "../Library/GameObject.h"

using namespace std;

class Common :public GameObject
{
public:
	Common();
	int Speed(string mode);

	int remAmmo;
	int remGAmmo;
	int nowStage;
	int weponNum;
	int score;
	int hiScore;
	int textFont[100];
	int mod[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };

	const int speedX = 12;
	const int speedrange[10] = { 2,2,2,0,2 };
	const int objPattern_A[10] = { 6,13,7,0,0 };
	const int objPattern_B[10] = { 0,0,5,0,0 };

	bool cleared = FALSE;

	bool dontClear = FALSE;
	bool debugmode = FALSE;
};