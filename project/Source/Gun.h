#pragma once
#include "../Library/SceneBase.h"

class Gun : public SceneBase
{
public:
	Gun();
	~Gun();
	void Update() override;
	void Draw() override;

private:
	int gunImage;
};
