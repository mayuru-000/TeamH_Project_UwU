#pragma once
#include "../Library/GameObject.h"

class Target :public GameObject
{
public:
	Target();
	Target(int fx, int fy, int handle, int speed);
	~Target();
	void Update() override;
	void Draw() override;

	bool isHit(int px, int py, int damage);
private:
	int tImage;
	int x, y;
	int hp;
	int scrollX;
};
