#include "Common.h"

Common::Common()
{
	DontDestroyOnSceneChange();
	remAmmo = 0;
	remGAmmo = 0;
	weponNum = 0;

	score = 0;
	breakcount = 0;
	hiScore = 0;

	nowStage = 1;

	AddFontResourceExA("data/Font/POCKC___.TTF", FR_PRIVATE, NULL);
	textFont[0] = CreateFontToHandle("Pocket Calculator", 60, -1, -1);
	textFont[1] = CreateFontToHandle("Pocket Calculator", 125, -1, -1);
	textFont[2] = CreateFontToHandle("Pocket Calculator", 250, -1, -1);
}

int Common::Speed(string mode)
{
	if (mode == "front") { return speedX + speedrange[nowStage - 1]; }
	if (mode == "back") { return speedX - speedrange[nowStage - 1]; }
	return 0;
}

void Common::Init()
{
	score = 0;
	remAmmo = 0;
	remGAmmo = 0;
	weponNum = 0;
	breakcount = 0;
	nowStage = 1;

	reroading = FALSE;
	cleared = FALSE;
	gameCleared = FALSE;

	debugmode = FALSE;
	dontClear = FALSE;
	for (int i = 0;i < 9;i++) { mod[i] = -1; }
}
