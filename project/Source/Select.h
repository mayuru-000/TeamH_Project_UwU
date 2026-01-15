#pragma once
#include "../Library/GameObject.h"

class Select:public GameObject
{
public:
	Select();
	~Select();
	void Update() override;
	void Draw() override;

private:
	float c1, c2, c3;

	int x, y;
	int bgImage;
	int wImage1;
	int wImage2;
	int wImage3;
	int wTitleFont;
	int wExplanaFont;
	int wExplanaFont2;

	int nowSelect;
};