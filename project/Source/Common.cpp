#include "Common.h"

Common::Common()
{
	DontDestroyOnSceneChange();
	nowStage = 1;
	speedX = 5;

	atkBuf = 0;
	gunrateBuf = 0;
	maxammoBuf = 0;

	score = 0;
	hiScore = 0;

	std::string modlist[6] = { "attack","speed","maxbullet","bomAttack","bomRange","bomSup" };
}
