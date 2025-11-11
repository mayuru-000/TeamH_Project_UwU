#pragma once
#include "../Library/GameObject.h"

class Gun : public GameObject
{
public:
	Gun();
	~Gun();
	void Update() override;
	void Draw() override;

private:
	int gunImage;
};
