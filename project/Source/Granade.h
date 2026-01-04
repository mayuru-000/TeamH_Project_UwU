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
	int explDuration = 80;
	int radius = 500;  

	static const int num = 3;
	int range[num] = { 50,200,500 };
	int ammoDamage[num] = { 600,300,100 };
};

