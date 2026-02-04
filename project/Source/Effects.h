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
	void FadeOutBGM(float sec);

	void FadeIn(float sec);
	void FadeOut(float sec);
	void ResetAlpha() { reset = TRUE; }

	void setFlash(float sec) { 
		flashSpan = sec; }
	bool getFlash() { return flash; }

	void SetColor(int r, int g, int b) { rgb = GetColor(r, g, b); }
	bool Finished() { return now >= time; }

private:
	int selectSE, defineSE, transSE;
	int gunSE, assaultSE, explosionSE, launcherSE;
	int reroadingSE, reroadedSE;
	int hitSE[3], breakSE[3], parrySE;
	int clearSE, defeatSE, goalSE;
	int BGM, clearBGM;

	int alpha;
	int startAlpha;
	int endAlpha;

	int nowBGM;
	int nowVolume;

	float flashSpan;
	float flashCount;

	float time;
	float now;

	float bgmTime;
	float bgmNow;

	unsigned int rgb;

	bool reset = FALSE;
	bool flash = FALSE;
};
