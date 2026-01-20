#pragma once
#include "../Library/GameObject.h"

class GameClear:public GameObject
{
public:
	GameClear();
	~GameClear();
	void Update() override;
	void Draw() override;
private:
	int scImage;
	int bgImage;
	int abcImage[10];

	float y;
	int s, b, t;
	int Width;
	int scoreDigit;
	int breakDigit;
	int tScoreDigit;
	int totalscore;

	bool moveY;
	bool newrecord;
};