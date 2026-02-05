#pragma once
#include <string>
#include "../Library/GameObject.h"

using namespace std;

class Common :public GameObject
{
public:
	Common();
	int Speed(string mode);
	void ScoreLoad();
	void ScoreSave();
	void Init();
	int remAmmo;
	int remGAmmo;
	int nowStage;
	int weponNum;
	int score;
	int breakcount;
	int rastCharge;
	int textFont[100];

	int gnHiScore;
	int asHiScore;
	int rkHiScore;

	int mod[9] = { -1,-1,-1,-1,-1,-1,-1,-1,-1 };
	//int mod[9] = { 5,5,5,5,5,1,-1,-1,-1 };
	int gnRanking[3] = { 0,0,0 };
	int asRanking[3] = { 0,0,0 };
	int rkRanking[3] = { 0,0,0 };
	//int gnRanking[3] = { 1111,111,11 };
	//int asRanking[3] = { 2222,222,22 };
	//int rkRanking[3] = { 3333,333,33 };


	const int speedX = 12;
	const int speedrange[10] = { 3,3,3,4,4,4,5,5,6 };
	const int objPattern_A[10] = { 6,14,7,5,5,7,14,6,9 };
	const int objPattern_B[10] = { 0,0,5,3,3,5,0,1,1 };

	bool reroading = FALSE;
	bool cleared = FALSE;
	bool gameCleared = FALSE;

	bool dontClear = FALSE;
	bool debugmode = FALSE;

};