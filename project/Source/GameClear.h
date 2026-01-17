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
	int abcImage[3];

	int s, b;
	int Width;
	int scoreDigit;
	int breakDigit;
};