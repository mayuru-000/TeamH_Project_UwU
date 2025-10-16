#pragma once
#include "../Library/SceneBase.h"


class Field : public SceneBase
{
public:
	Field();
	~Field();
	void Update() override;
	void Draw() override;

private:
	int fImage;
};