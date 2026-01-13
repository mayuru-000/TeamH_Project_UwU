#pragma once
#include "../Library/GameObject.h"

class Debug :public GameObject
{
public:
	Debug();
	~Debug();
	void Update() override;
	void Draw() override;

private:
	bool prevPush;
};