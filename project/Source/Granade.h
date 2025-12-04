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
	int exploImage;
	int GranadeImage;
	int ExplosionSE;
	int Gammo = 5;
	int x = 0;
	int y = 0;
	int gx = 0;
	int gy = 0;
	
	bool exploding = false;
	int explTimer = 0;
	int explDuration = 100;
	int radius = 300;  
};

