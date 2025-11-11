#pragma once
#include "../Library/GameObject.h"

class Player : public GameObject
{
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;

private:
	int pImage;
	int x = 0;
	int y = 0;
	float Expansion = 0.1;
	float ExpansionRate = 0.005;
};
