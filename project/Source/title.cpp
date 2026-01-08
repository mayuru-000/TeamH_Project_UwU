#include "title.h"
#include "Select.h"
#include "Screen.h"
#include "Effects.h"

title::title()
{
	spaceInputed = FALSE;
	bgImage = LoadGraph("data/image/bg/bg_pre.png");
	tImage = LoadGraph("data/image/title_pre.png");
	carImage = LoadGraph("data/image/car.png");

	x = -300;
	y = -200;
	count = 0;
	flameCounter = 0;
}

title::~title()
{
}

void title::Update()
{
	Effects* e = FindGameObject<Effects>();

	x += 5;;
	flameCounter++;
	if (x > Screen::WIDTH) { x =- 300; }
	if (flameCounter == 60) { flameCounter = 0; }
	count = flameCounter / 30;

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		if (!spaceInputed) {
			spaceInputed = TRUE;
			e->playSE("define", 300);
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
	DrawRectGraph(x, Screen::HEIGHT + y, 350 * count, 0, 350, 200, carImage, TRUE);

	if (!spaceInputed) {
		DrawGraph(193, 50, tImage, TRUE);
		y = -200;
	}
	else { y = -360; }

	//aaaa
	
	
}
