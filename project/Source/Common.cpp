#include "Common.h"

Common::Common()
{
	DontDestroyOnSceneChange();
	nowStage = -1;
	speedX = 5;

	atkBuf = 0;
	gunrateBuf = 0;
	maxammoBuf = 0;
}
