#include "GameClear.h"
#include "Gunsetting.h"
#include "Common.h"
#include "Field.h"
#include "Player.h"
#include "Effects.h"
#include "Screen.h"

GameClear::GameClear()
{
	Common* c = FindGameObject<Common>();
	Effects* e = FindGameObject<Effects>();
	Field* field = FindGameObject<Field>();
	Player* player = FindGameObject<Player>();
	Gunsetting* Gset = FindGameObject<Gunsetting>();

	e->FadeIn(2);
	e->playSE("clearBGM", 200);
	c->cleared = FALSE;
	c->gameCleared = TRUE;
	Gset->DestroyMe();
	field->DestroyMe();
	player->DestroyMe();

	totalscore = c->score + (c->breakcount * 1000);

	newrecord = FALSE;
	if (totalscore > c->hiScore) {
		newrecord = TRUE;
		c->hiScore = totalscore;
	}

	abcImage[0] = LoadGraph("data/image/icon/score_s.png");
	abcImage[1] = LoadGraph("data/image/icon/score_a.png");
	abcImage[2] = LoadGraph("data/image/icon/score_b.png");
	abcImage[3] = LoadGraph("data/image/icon/score_c.png");
	bgImage = LoadGraph("data/image/bg/gameClear_bg.png");
	scImage = LoadGraph("data/image/bg/gameClear_box.png");

	y = 0;
	Width = 0;
	scoreDigit = 1;
	breakDigit = 1;
	tScoreDigit = 1;
	s = c->score;
	b = c->breakcount;
	t = totalscore;
	while (s >= 9)
	{
		s /= 10;
		scoreDigit++;
	}
	while (b >= 9)
	{
		b /= 10;
		breakDigit++;
	}
	while (t >= 9) 
	{
		t /= 10;
		tScoreDigit++;
	}
}

GameClear::~GameClear()
{
}

void GameClear::Update()
{
	Common* c = FindGameObject<Common>();
	Effects* e = FindGameObject<Effects>();

	if (moveY) { 
		y -= 0.2;
		if (y <= -10) {
			moveY = !moveY;
		}
	}
	else { 
		y += 0.2;
		if (y >= 0) {
			moveY = !moveY;
		}
	}
	if (e->Finished()) {
		if (!c->gameCleared) {
			c->Init();
			c->cleared = FALSE;
			SceneManager::ChangeScene("TITLE");
		}
		if (GetMouseInput() & MOUSE_INPUT_LEFT) {
			e->FadeOut(2);
			e->FadeOutBGM(2);
			c->gameCleared = FALSE;
		}

	}
}

void GameClear::Draw()
{
	Common* c = FindGameObject<Common>();
	Effects* e = FindGameObject<Effects>();

	DrawGraph(0, 0, bgImage, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 130);
	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawGraph(0, 0, scImage, TRUE);

	Width = GetDrawFormatStringWidthToHandle(c->textFont[1], "0");

	//SCORE
	DrawFormatStringToHandle(205, 135, GetColor(0, 0, 0), c->textFont[0], "SCORE:");
	DrawFormatStringToHandle(200, 130, GetColor(253, 163, 4), c->textFont[0], "SCORE:");
	for (int i = 0;i < 8 - scoreDigit;i++) 
	{
		DrawFormatStringToHandle(210 + Width * i, 180, GetColor(0, 0, 0), c->textFont[1], "0");
		DrawFormatStringToHandle(200 + Width * i, 170, GetColor(150, 150, 150), c->textFont[1], "0");
	}
	DrawFormatStringToHandle(210 + Width * (8 - scoreDigit), 180, GetColor(0, 0, 0), c->textFont[1], "%d", c->score);
	DrawFormatStringToHandle(200 + Width * (8 - scoreDigit), 170, GetColor(255, 255, 255), c->textFont[1], "%d", c->score);

	//BREAK
	DrawFormatStringToHandle(205, 285, GetColor(0, 0, 0), c->textFont[0], "BREAK:");
	DrawFormatStringToHandle(200, 280, GetColor(253, 163, 4), c->textFont[0], "BREAK:");
	for (int i = 0;i < 8 - breakDigit;i++)
	{
		DrawFormatStringToHandle(210 + Width * i, 330, GetColor(0, 0, 0), c->textFont[1], "0");
		DrawFormatStringToHandle(200 + Width * i, 320, GetColor(150, 150, 150), c->textFont[1], "0");
	}
	DrawFormatStringToHandle(210 + Width * (8 - breakDigit), 330, GetColor(0, 0, 0), c->textFont[1], "%d", c->breakcount);
	DrawFormatStringToHandle(200 + Width * (8 - breakDigit), 320, GetColor(255, 255, 255), c->textFont[1], "%d", c->breakcount);
	
	//TOTAL
	DrawFormatStringToHandle(205, 475, GetColor(0, 0, 0), c->textFont[0], "TOTAL:");
	DrawFormatStringToHandle(200, 470, GetColor(253, 163, 4), c->textFont[0], "TOTAL:");
	for (int i = 0;i < 8 - tScoreDigit;i++)
	{
		DrawFormatStringToHandle(410 + Width * i, 480, GetColor(0, 0, 0), c->textFont[1], "0");
		DrawFormatStringToHandle(400 + Width * i, 470, GetColor(150, 150, 150), c->textFont[1], "0");
	}
	if (newrecord) {
		e->setFlash(0.05);
		if (e->getFlash()) {
			DrawFormatStringToHandle(410 + Width * (8 - tScoreDigit), 480, GetColor(0, 0, 0), c->textFont[1], "%d", totalscore);
			DrawFormatStringToHandle(400 + Width * (8 - tScoreDigit), 470, GetColor(255, 0, 0), c->textFont[1], "%d", totalscore);
		}
		else{
			DrawFormatStringToHandle(410 + Width * (8 - tScoreDigit), 480, GetColor(0, 0, 0), c->textFont[1], "%d", totalscore);
			DrawFormatStringToHandle(400 + Width * (8 - tScoreDigit), 470, GetColor(255, 255, 0), c->textFont[1], "%d", totalscore);
		}
		//e->setFlash(0.12);
	}
	else{
		DrawFormatStringToHandle(410 + Width * (8 - tScoreDigit), 480, GetColor(0, 0, 0), c->textFont[1], "%d", totalscore);
		DrawFormatStringToHandle(400 + Width * (8 - tScoreDigit), 470, GetColor(255, 255, 255), c->textFont[1], "%d", totalscore);
	}


	DrawGraph(700, 130 + y, abcImage[0], TRUE);
	

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
