#pragma once
#include "../Library/GameObject.h"

class Granade : public GameObject
{
public:
	Granade();
	~Granade();
	void Update() override;
	void Draw() override;

private:
	int gImage;
};

