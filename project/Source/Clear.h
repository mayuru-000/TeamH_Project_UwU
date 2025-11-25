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

	void getUpdateKey();

private:
	int nowSelect;
	char Key[256];
	char modList[10];
};