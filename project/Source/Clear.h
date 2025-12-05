#pragma once
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

	int nowSelect;
	bool prevPush;
};