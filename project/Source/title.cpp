#include "title.h"
#include "Select.h"

title::title()
{
	spaceInputed = FALSE;
	bgImage = LoadGraph("data/image/bg_pre.png");
	tImage = LoadGraph("data/image/title_pre.png");
}

title::~title()
{
}

void title::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		if (!spaceInputed) {
			spaceInputed = TRUE;
			new Select();
		}
	}
	if (CheckHitKey(KEY_INPUT_BACK)) {
		spaceInputed = FALSE;
	}
}

void title::Draw()
{
	DrawGraph(0, 0, bgImage, TRUE);

	if (!spaceInputed) {
		DrawGraph(193, 50, tImage, TRUE);
	}
}
