#pragma once
#include <vector>
#include <algorithm>
#include "../Library/GameObject.h"

class Clear:public GameObject
{
public:
	Clear();
	Clear(int score);
	~Clear();

	void Update()override;
	void Draw()override;

	void selected();
private:
	int bgImage;
	int bufImage;

	int count;
	int nowSelect;
	bool prevPush;

	int  buffs[3];
};