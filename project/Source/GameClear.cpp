#include "GameClear.h"
#include "Gunsetting.h"
#include "Common.h"
#include "Field.h"
#include "Player.h"
#include "Screen.h"

GameClear::GameClear()
{
	Common* c = FindGameObject<Common>();
	Field* field = FindGameObject<Field>();
	Player* player = FindGameObject<Player>();
	Gunsetting* Gset = FindGameObject<Gunsetting>();

	c->cleared = FALSE;
	Gset->DestroyMe();
	field->DestroyMe();
	player->DestroyMe();

	abcImage[0] = LoadGraph("data/image/icon/score_a.png");
	abcImage[1] = LoadGraph("data/image/icon/score_b.png");
	abcImage[2] = LoadGraph("data/image/icon/score_c.png");
	bgImage = LoadGraph("data/image/bg/bg_pre.png");
	scImage = LoadGraph("data/image/bg/gameClear_bg.png");


	Width = 0;
	scoreDigit = 0;
	breakDigit = 0;
	s = c->score;
	b = c->breakcount;
	while (s != 0)
	{
		s /= 10;
		scoreDigit++;
	}
	while (b != 0)
	{
		b /= 10;
		breakDigit++;
	}
}

GameClear::~GameClear()
{
}

void GameClear::Update()
{
}

void GameClear::Draw()
{
	Common* c = FindGameObject<Common>();

	DrawGraph(0, 0, bgImage, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 130);
	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawGraph(0, 0, scImage, TRUE);

	Width = GetDrawFormatStringWidthToHandle(c->textFont[1], "0");

	DrawFormatStringToHandle(205, 135, GetColor(0, 0, 0), c->textFont[0], "SCORE:");
	DrawFormatStringToHandle(200, 130, GetColor(253, 163, 4), c->textFont[0], "SCORE:");
	for (int i = 0;i < 7 - scoreDigit;i++) 
	{
		DrawFormatStringToHandle(210 + Width * i, 180, GetColor(0, 0, 0), c->textFont[1], "0", c->score);
		DrawFormatStringToHandle(200 + Width * i, 170, GetColor(150, 150, 150), c->textFont[1], "0", c->score);
	}
	DrawFormatStringToHandle(210 + Width * (7 - scoreDigit), 180, GetColor(0, 0, 0), c->textFont[1], "%d", c->score);
	DrawFormatStringToHandle(200 + Width * (7 - scoreDigit), 170, GetColor(255, 255, 255), c->textFont[1], "%d", c->score);


	DrawFormatStringToHandle(205, 285, GetColor(0, 0, 0), c->textFont[0], "BREAK:");
	DrawFormatStringToHandle(200, 280, GetColor(253, 163, 4), c->textFont[0], "BREAK:");
	for (int i = 0;i < 7 - breakDigit;i++)
	{
		DrawFormatStringToHandle(210 + Width * i, 330, GetColor(0, 0, 0), c->textFont[1], "0", c->score);
		DrawFormatStringToHandle(200 + Width * i, 320, GetColor(150, 150, 150), c->textFont[1], "0", c->score);
	}
	DrawFormatStringToHandle(210 + Width * (7 - breakDigit), 330, GetColor(0, 0, 0), c->textFont[1], "%d", c->breakcount);
	DrawFormatStringToHandle(200 + Width * (7 - breakDigit), 320, GetColor(255, 255, 255), c->textFont[1], "%d", c->breakcount);

	DrawGraph(700, 130, abcImage[0], TRUE);
	
	/*debug*/
	if (c->debugmode) {
		for (int i = 0;i <= Screen::WIDTH / 10;i++) {
			DrawLine(10 * i, 0, 10 * i, Screen::HEIGHT, GetColor(255, 255, 255), 1);
			DrawLine(100 * i, 0, 100 * i, Screen::HEIGHT, GetColor(255, 0, 0), 2);
		}
		for (int i = 0;i <= Screen::HEIGHT / 10;i++) {
			DrawLine(0, 10 * i, Screen::WIDTH, 10 * i, GetColor(255, 255, 255), 1);
			DrawLine(0, 100 * i, Screen::WIDTH, 100 * i, GetColor(255, 0, 0), 2);
		}
	}
}
