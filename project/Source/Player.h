#pragma once
#include "../Library/SceneBase.h"

class Player : public SceneBase
{
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;

private:
	int pImage;
};
