#pragma once
#include "../Library/GameObject.h"

enum class MODE
{
	SELECT,
	TUTORIAL_1,
	TUTORIAL_2,
};

class Select:public GameObject
{
public:
	Select();
	~Select();
	void Update() override;
	void Draw() override;

private:
	MODE mode;
	float c1, c2, c3;

	int x, y;
	int weponImage;
	int bgImage;
	int wImage1;
	int wImage2;
	int wImage3;
	int tutorial1;
	int tutorial2;
	int bufImage;
	int wTitleFont;
	int wExplanaFont;
	int wExplanaFont2;

	int nowSelect;

	float Time;
	float nowTime;
	float DeltaTime;

	bool check = FALSE;
};