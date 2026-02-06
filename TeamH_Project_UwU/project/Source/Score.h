#pragma once
#include "../Library/GameObject.h"

class Score:public GameObject
{
public:
	Score();
	Score(int px, int py, int pscore);
	~Score();
	void Update() override;
	void Draw() override;

private:
	int x, y;
	int score;
	int count;
	char txtWidth;
};
