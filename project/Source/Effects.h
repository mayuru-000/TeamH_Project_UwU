#pragma once
#include "../Library/GameObject.h"

class Effects:public GameObject
{
public:

	Effects();
	~Effects();
	void Update()override;
	void Draw()override;

	void playSE(const char* name, int vol);

	void FadeIn(float sec);
	void FadeOut(float sec);

	void SetColor(int r, int g, int b) { rgb = GetColor(r, g, b); }
	bool Finished() { return now >= time; }

private:
	int selectSE, defineSE;
	int gunSE, assaultSE, explosionSE, outAmmoSE;
	int reroadingSE, reroadedSE;
	int hitSE[3], breakSE[3], parrySE;
	int clearSE, defeatSE, goalSE;
	int BGM;

	int alpha;
	int startAlpha;
	int endAlpha;

	float time;
	float now;

	unsigned int rgb;
};
