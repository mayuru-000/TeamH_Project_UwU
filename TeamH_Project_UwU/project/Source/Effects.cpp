#include "Effects.h"
#include "Common.h"
#include "Screen.h"

Effects::Effects()
{
	DontDestroyOnSceneChange();
	SetDrawOrder(-10000000);

	alpha = 0;
	startAlpha = 0;
	endAlpha = 0;
	time = 0;
	now = 0;
	rgb = 0;
	bgmTime = 0;
	bgmNow = 0;

	nowVolume = 0;
	flashCount = 0;
	flashSpan = 0.12;

	selectSE = LoadSoundMem("data/sound/se/select.mp3");
	defineSE = LoadSoundMem("data/sound/se/define.mp3");
	transSE = LoadSoundMem("data/sound/se/transition.mp3");

	gunSE = LoadSoundMem("data/Sound/SE/Gun.mp3");
	assaultSE = LoadSoundMem("data/Sound/SE/Assault.mp3");
	reroadingSE = LoadSoundMem("data/Sound/SE/reroad.mp3");
	reroadedSE = LoadSoundMem("data/Sound/SE/reroad_end.mp3");
	explosionSE = LoadSoundMem("data/Sound/SE/Explosion.mp3");
	launcherSE = LoadSoundMem("data/Sound/SE/launcher.mp3");

	hitSE[0] = LoadSoundMem("data/Sound/SE/hit_1.mp3");
	hitSE[1] = LoadSoundMem("data/Sound/SE/hit_2.mp3");
	hitSE[2] = LoadSoundMem("data/Sound/SE/hit_3.mp3");
	breakSE[0] = LoadSoundMem("data/Sound/SE/break_1.mp3");
	breakSE[1] = LoadSoundMem("data/Sound/SE/break_2.mp3");
	breakSE[2] = LoadSoundMem("data/Sound/SE/break_3.mp3");
	parrySE = LoadSoundMem("data/Sound/SE/parry.mp3");

	BGM = LoadSoundMem("data/sound/bgm/yuta's_bgm.wav");
	clearBGM = LoadSoundMem("data/sound/bgm/yuta's_clearBgm.wav");

	nowBGM = BGM;
}

Effects::~Effects()
{
	InitSoundMem();
}

void Effects::Update()
{
	if (!reset) {
		if (now < time) {
			now += Time::DeltaTime();
			float rate = now / time;
			alpha = (endAlpha - startAlpha) * rate + startAlpha;
		}
		else {
			alpha = endAlpha;
		}
	}
	else{
		now = 0;
		time = 0;
		alpha = 0;
		endAlpha = 0;
		reset = FALSE;
	}

	if (nowVolume > 0) {
		if (bgmNow < bgmTime) {
			bgmNow += Time::DeltaTime();
			float rate = 1 - (bgmNow / bgmTime);
			ChangeVolumeSoundMem(nowVolume * rate, nowBGM);
			if (rate <= 0) {
				nowVolume = 0;
				StopSoundMem(nowBGM);
			}
		}
	}

	if (flashCount >= flashSpan) {
		flashCount = 0;
		flash = !flash;
	}
	else {
		flashCount += Time::DeltaTime();
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
	ChangeNextPlayVolumeSoundMem(vol, reroadedSE);
	ChangeNextPlayVolumeSoundMem(vol, gunSE);
	ChangeNextPlayVolumeSoundMem(vol, assaultSE);
	ChangeNextPlayVolumeSoundMem(vol, explosionSE);
	ChangeNextPlayVolumeSoundMem(vol, launcherSE);
	ChangeNextPlayVolumeSoundMem(vol, hitSE[i]);
	ChangeNextPlayVolumeSoundMem(vol, breakSE[i]);
	ChangeNextPlayVolumeSoundMem(vol, parrySE);

	ChangeNextPlayVolumeSoundMem(vol, BGM);
	ChangeNextPlayVolumeSoundMem(vol, clearBGM);

	if (name == nullptr) return;
	if (name == "select") { PlaySoundMem(selectSE, DX_PLAYTYPE_BACK); }
	if (name == "define") { PlaySoundMem(defineSE, DX_PLAYTYPE_BACK); }
	if (name == "trans") { PlaySoundMem(transSE, DX_PLAYTYPE_BACK); }

	if (name == "reroading") { PlaySoundMem(reroadingSE, DX_PLAYTYPE_BACK); }
	if (name == "reroaded")  { PlaySoundMem(reroadedSE, DX_PLAYTYPE_BACK); }
	if (name == "assault")   { PlaySoundMem(assaultSE, DX_PLAYTYPE_BACK); }
	if (name == "launcher")  { PlaySoundMem(launcherSE, DX_PLAYTYPE_BACK); }
	if (name == "bomb")	     { PlaySoundMem(explosionSE, DX_PLAYTYPE_BACK); }
	if (name == "gun")       { PlaySoundMem(gunSE, DX_PLAYTYPE_BACK); }

	if (name == "hit")   { PlaySoundMem(hitSE[i], DX_PLAYTYPE_BACK); }
	if (name == "break") { PlaySoundMem(breakSE[i], DX_PLAYTYPE_BACK); }
	if (name == "parry") { PlaySoundMem(parrySE, DX_PLAYTYPE_BACK); }

	if (name == "BGM")	 { 
		if (CheckSoundMem(BGM) == 0) { 
			PlaySoundMem(BGM, DX_PLAYTYPE_LOOP); 
			nowBGM = BGM;
		}
	}
	if (name == "clearBGM") {
		if (CheckSoundMem(clearBGM) == 0) {
			PlaySoundMem(clearBGM, DX_PLAYTYPE_LOOP);
			nowBGM = clearBGM;
		}
	}

	if (name == "stopBGM") {
		StopSoundMem(nowBGM);
	}
}

void Effects::FadeOutBGM(float sec)
{
	nowVolume = GetVolumeSoundMem2(nowBGM);
	bgmTime = sec;
	bgmNow = 0;
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

