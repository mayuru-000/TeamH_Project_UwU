#pragma once
#include "../Library/GameObject.h"

class Select:public GameObject
{
public:
	Select();
	~Select();
	void Update() override;
	void Draw() override;

	void getUpdateKey();

private:
	float c1, c2, c3;

	int bgImage;
	int wImage1;
	int wImage2;
	int wImage3;
	int wTitleFont;
	int wExplanaFont;
	int wExplanaFont2;

	int nowSelect;
	char Key[256];
};