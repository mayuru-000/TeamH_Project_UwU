#pragma once
#include <string>
#include "../Library/GameObject.h"

using namespace std;

class Common :public GameObject
{
public:
	Common();
	int Speed(string mode);
	void Init();
	int remAmmo;
	int remGAmmo;
	int nowStage;
	int weponNum;
	int score;
	int hiScore;
	int breakcount;
	int textFont[100];
	//int mod[9] = { -1,-1,-1,-1,-1,-1,-1,-1,-1 };
	int mod[9] = { 1,1,1,1,1,1,-1,-1,-1 };

	const int speedX = 12;
	const int speedrange[10] = { 3,3,3,3,3 };
	const int objPattern_A[10] = { 6,13,7,0,0 };
	const int objPattern_B[10] = { 0,0,5,0,0 };

	bool reroading = FALSE;
	bool cleared = FALSE;
	bool gameCleared = FALSE;

	bool dontClear = FALSE;
	bool debugmode = FALSE;
};