#include "Debug.h"

Debug::Debug()
{
	Debugmode = FALSE;
	prevPush = FALSE;
}

Debug::~Debug()
{
}

void Debug::Update()
{
	if (CheckHitKey(KEY_INPUT_R)) {
		if (!prevPush) {
			Debugmode != Debugmode;
			prevPush = TRUE;
		}
	}
	else{
		prevPush = FALSE;
	}
}

void Debug::Draw()
{
	DrawString(100, 0, "DEBUG MODE", GetColor(0, 0, 0));
}
