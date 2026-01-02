#pragma once
#include "../Library/GameObject.h"

class Effects:public GameObject
{
public:
	Effects();
	~Effects();

	void Update()override;
	void Draw()override;
private:

};
