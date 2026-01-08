#include "Common.h"

Common::Common()
{
	DontDestroyOnSceneChange();
	nowStage = 1;
	speedX = 6;

	atkBuf = 0;
	gunrateBuf = 0;
	maxammoBuf = 0;

	score = 0;
	hiScore = 0;

	std::string modlist[6] = { "attack","speed","maxbullet","bomAttack","bomRange","bomSup" };
}

int Common::Speed(string mode)
{
	if (mode == "front") { return speedX + speedrange[nowStage]; }
	if (mode == "back") { return speedX - speedrange[nowStage]; }

	return 0;
}
