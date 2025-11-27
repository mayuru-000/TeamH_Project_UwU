#pragma once
#include "../Library/GameObject.h"

class Target:public GameObject
{
public:
	Target();
	Target(int fx,int fy,int handle);
	~Target();
	void Update() override;
	void Draw() override;
private:

};
