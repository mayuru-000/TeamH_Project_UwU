#include "Score.h"
#include "Common.h"
#include "Screen.h"

Score::Score()
{
}

Score::Score(int px, int py, int pscore)
{
	Common* c = FindGameObject<Common>();
	x = px;
	y = py;

	count = 0;
	score = pscore;
	c->score += pscore;

	txtWidth = GetDrawFormatStringWidthToHandle(c->textFont[0], "%d", score);
}

Score::~Score()
{
}

void Score::Update()
{
	Common* c = FindGameObject<Common>();

	y -= 2;
	count += 4;
	x -= c->speedX;

	if (count > 100) {
		DestroyMe();
	}
}

void Score::Draw()
{
	Common* c = FindGameObject<Common>();
	DrawFormatStringToHandle(x - (txtWidth / 2), y, GetColor(255, 0, 0), c->textFont[0], "+%d", score);
}
