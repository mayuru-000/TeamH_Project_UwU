#include "Common.h"

Common::Common()
{
	DontDestroyOnSceneChange();
	weponNum = 0;
	score = 0;
	hiScore = 0;

	nowStage = 2;

	AddFontResourceExA("data/Font/POCKC___.TTF", FR_PRIVATE, NULL);
	textFont_1 = CreateFontToHandle("Pocket Calculator", 40, -1, -1);
	textFont_2 = CreateFontToHandle("Pocket Calculator", 250, -1, -1);
}

int Common::Speed(string mode)
{
	if (mode == "front") { return speedX + speedrange[nowStage - 1]; }
	if (mode == "back") { return speedX - speedrange[nowStage - 1]; }
	return 0;
}
