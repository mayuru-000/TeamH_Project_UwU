#pragma once
#include "../Library/GameObject.h"


class Field : public GameObject
{
public:
	Field();
	~Field();
	void Update() override;
	void Draw() override;

	bool isHit(int px, int py);
private:
	int fImage;
	int x, y;
};