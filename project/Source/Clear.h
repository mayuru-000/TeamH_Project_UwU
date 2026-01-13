#pragma once
#include <vector>
#include <algorithm>
#include "../Library/GameObject.h"

class Clear:public GameObject
{
public:
	Clear();
	~Clear();

	void Update()override;
	void Draw()override;

	void selected();
private:
	int bgImage;
	int bufImage;
	int cardImage;
	int cardDImage_1, cardDImage_2, cardDImage_3;
	int bufBgImage;
	int bufIcon;

	int count;
	int nowSelect;
	bool prevPush;

	int  buffs[3];
};