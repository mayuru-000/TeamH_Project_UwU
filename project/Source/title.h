#pragma once
#include "../Library/GameObject.h"

class title :public GameObject
{
public:
	title();
	~title();
	void Update() override;
	void Draw() override;

private:
	int i, count, flameCounter;
	int x, y;
	int carImage;
	int sbgImage;
	int bgImage;
	int tImage;
	bool spaceInputed;
};