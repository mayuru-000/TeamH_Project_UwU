#include "Effects.h"
#include "Screen.h"

Effects::Effects()
{
	DontDestroyOnSceneChange();
	SetDrawOrder(-10000);

	alpha = 0;
	startAlpha = 0;
	endAlpha = 0;
	time = 0;
	now = 0;
	rgb = 0;

	selectSE = LoadSoundMem("data/sound/se/select.mp3");
	defineSE = LoadSoundMem("data/sound/se/define.mp3");
}

Effects::~Effects()
{
	DeleteSoundMem(selectSE);
	DeleteSoundMem(defineSE);
}

void Effects::Update()
{
	if (now < time) {
		now += Time::DeltaTime();
		float rate = now / time;
		alpha = (endAlpha - startAlpha) * rate + startAlpha;
	}
	else {
		alpha = endAlpha;
	}
	
}

void Effects::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, rgb, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Effects::playSE(const char* name)
{
	if (name == nullptr) return;
	if (name == "select") { PlaySoundMem(selectSE, DX_PLAYTYPE_BACK); }
	if (name == "define") { PlaySoundMem(defineSE, DX_PLAYTYPE_BACK); }
}

void Effects::FadeIn(float sec)
{
	startAlpha = 255;
	endAlpha = 0;
	time = sec;
	now = 0;
}

void Effects::FadeOut(float sec)
{
	startAlpha = 0;
	endAlpha = 255;
	time = sec;
	now = 0;
}

