#pragma once
#include "../Library/GameObject.h"

enum class MODE
{
	RESULTS,
	RANKING,
};

class GameClear:public GameObject
{
public:
	GameClear();
	~GameClear();
	void Update() override;
	void Draw() override;
private:
	MODE mode;
	int checkDigit(int num);

	int scImage;
	int bgImage;
	int abcImage[10];

	float x;
	float y;
	int Width;
	int rWidth;

	int scoreDigit;
	int breakDigit;
	int tScoreDigit;
	int rank1Digit;
	int rank2Digit;
	int rank3Digit;
	int ranking[3];

	int rank = 0;
	int totalscore;

	bool moveY = FALSE;
	bool rankIn = FALSE;
	bool newrecord = FALSE;

	bool changing = FALSE;
};