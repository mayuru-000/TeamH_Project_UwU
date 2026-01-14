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

	gunSE = LoadSoundMem("data/Sound/SE/Gun.mp3");
	assaultSE = LoadSoundMem("data/Sound/SE/Assault.mp3");
	reroadingSE = LoadSoundMem("data/Sound/SE/reroaro.mp3");
	//reroadedSE = LoadSoundMem("data/Sound/SE/");
	explosionSE = LoadSoundMem("data/Sound/SE/Explosion.mp3");
	//outAmmoSE= LoadSoundMem("data/Sound/SE/");

	hitSE[0] = LoadSoundMem("data/Sound/SE/hit_1.mp3");
	hitSE[1] = LoadSoundMem("data/Sound/SE/hit_2.mp3");
	hitSE[2] = LoadSoundMem("data/Sound/SE/hit_3.mp3");
	breakSE[0] = LoadSoundMem("data/Sound/SE/break_1.mp3");
	breakSE[1] = LoadSoundMem("data/Sound/SE/break_2.mp3");
	breakSE[2] = LoadSoundMem("data/Sound/SE/break_3.mp3");
	parrySE = LoadSoundMem("data/Sound/SE/parry.mp3");
}

Effects::~Effects()
{
	InitSoundMem();
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

void Effects::playSE(const char* name, int vol)
{
	int i = GetRand(2);
	ChangeNextPlayVolumeSoundMem(vol, selectSE);
	ChangeNextPlayVolumeSoundMem(vol, defineSE);
	ChangeNextPlayVolumeSoundMem(vol, reroadingSE);
	//ChangeNextPlayVolumeSoundMem(vol, reroadedSE);
	ChangeNextPlayVolumeSoundMem(vol, gunSE);
	ChangeNextPlayVolumeSoundMem(vol, assaultSE);
	ChangeNextPlayVolumeSoundMem(vol, explosionSE);
	//ChangeNextPlayVolumeSoundMem(vol, outAmmoSE);
	ChangeNextPlayVolumeSoundMem(vol, hitSE[i]);
	ChangeNextPlayVolumeSoundMem(vol, breakSE[i]);
	ChangeNextPlayVolumeSoundMem(vol, parrySE);

	if (name == nullptr) return;
	if (name == "select") { PlaySoundMem(selectSE, DX_PLAYTYPE_BACK); }
	if (name == "define") { PlaySoundMem(defineSE, DX_PLAYTYPE_BACK); }

	if (name == "reroading") { PlaySoundMem(reroadingSE, DX_PLAYTYPE_BACK); }
	if (name == "reroaded")  {}
	if (name == "assault")   { PlaySoundMem(assaultSE, DX_PLAYTYPE_BACK); }
	if (name == "bomb")	     { PlaySoundMem(explosionSE, DX_PLAYTYPE_BACK); }
	if (name == "gun")       { PlaySoundMem(gunSE, DX_PLAYTYPE_BACK); }
	if (name == "outAmmo")	 {}

	if (name == "hit")   { PlaySoundMem(hitSE[i], DX_PLAYTYPE_BACK); }
	if (name == "break") { PlaySoundMem(breakSE[i], DX_PLAYTYPE_BACK); }
	if (name == "parry") { PlaySoundMem(parrySE, DX_PLAYTYPE_BACK); }
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

