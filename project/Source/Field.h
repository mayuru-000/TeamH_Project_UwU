#pragma once
#include "../Library/GameObject.h"


class Field : public GameObject
{
public:
	Field();
	~Field();
	void Update() override;
	void Draw() override;

private:
	int fImage;
};