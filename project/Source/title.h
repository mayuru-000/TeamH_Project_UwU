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
	int i;

	int sbgImage;
	int bgImage;
	int tImage;
	bool spaceInputed;
};