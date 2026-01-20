#include "title.h"
#include "Select.h"
#include "Screen.h"
#include "Effects.h"

title::title()
{
	prevPush = FALSE;
	spaceInputed = FALSE;
	bgImage = LoadGraph("data/image/bg/bg_pre.png");
	tImage = LoadGraph("data/image/title.png");
	carImage = LoadGraph("data/image/car.png");

	x = -300;
	y = -200;
	count = 0;
	flameCounter = 0;
}

title::~title()
{
	DeleteGraph(bgImage);
	DeleteGraph(tImage);
	DeleteGraph(carImage);	
}

void title::Update()
{
	Effects* e = FindGameObject<Effects>();

	x += 5;;
	flameCounter++;
	if (x > Screen::WIDTH) { x =- 300; }
	if (flameCounter == 60) { flameCounter = 0; }
	count = flameCounter / 30;

	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		if (!spaceInputed) {
			prevPush = TRUE;
			spaceInputed = TRUE;
			e->playSE("define", 300);
			new Select();
		}
	}else{
		prevPush = FALSE;
	}

	if (CheckHitKey(KEY_INPUT_BACK) || CheckHitKey(KEY_INPUT_O)) {
		spaceInputed = FALSE;
	}
}

void title::Draw()
{
	DrawGraph(0, 0, bgImage, TRUE);
	DrawRectGraph(x, Screen::HEIGHT + y, 350 * count, 0, 350, 200, carImage, TRUE);

	if (!spaceInputed) {
		DrawGraph(0, 0, tImage, TRUE);
		y = -200;
	}
	else { y = -360; }
}
