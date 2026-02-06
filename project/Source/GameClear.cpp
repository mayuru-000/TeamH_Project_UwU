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

	abcImage[0] = LoadGraph("data/image/icon/score_s.png");
	abcImage[1] = LoadGraph("data/image/icon/score_a.png");
	abcImage[2] = LoadGraph("data/image/icon/score_b.png");
	abcImage[3] = LoadGraph("data/image/icon/score_c.png");
	bgImage = LoadGraph("data/image/bg/gameClear_bg.png");
	scImage = LoadGraph("data/image/bg/gameClear_box.png");

	x = 0;
	y = 0;
	Width = 0;
	rank = 0;
	rate = 'C';
	scoreDigit =  checkDigit(c->score);
	breakDigit =  checkDigit(c->breakcount);
	tScoreDigit = checkDigit(totalscore);

	switch (c->weponNum)
	{
	case 1:
		if (totalscore > c->gnHiScore) {
			newrecord = TRUE;
			c->gnHiScore = totalscore;
		}
		for (int i = 0;i < 3;i++) {
			if (totalscore > c->gnRanking[i]) {
				rankIn = TRUE;
				rank = i + 1;
				for (int j = 2;j > i;j--) {
					c->gnRanking[j] = c->gnRanking[j - 1];
				}
				c->gnRanking[i] = totalscore;
				
				i = 100;								//更新したらブレイク
			}
		}

		rank1Digit = checkDigit(c->gnRanking[0]);
		rank2Digit = checkDigit(c->gnRanking[1]);
		rank3Digit = checkDigit(c->gnRanking[2]);
		for (int i = 0;i < 3;i++) { ranking[i] = c->gnRanking[i]; }

		if		(totalscore >= 800000)	{ rate = 'S'; }
		else if (totalscore >= 770000)	{ rate = 'A'; }
		else if (totalscore >= 650000)	{ rate = 'B'; }
		else							{ rate = 'C'; }

		break;

	case 2:
		if (totalscore > c->asHiScore) {
			newrecord = TRUE;
			c->asHiScore = totalscore;
		}
		for (int i = 0;i < 3;i++) {
			if (totalscore > c->asRanking[i]) {
				rankIn = TRUE;
				rank = i + 1;
				for (int j = 2;j > i;j--) {
					c->asRanking[j] = c->asRanking[j - 1];
				}
				c->asRanking[i] = totalscore;
				
				i = 100;								//更新したらブレイク
			}
		}
		rank1Digit = checkDigit(c->asRanking[0]);
		rank2Digit = checkDigit(c->asRanking[1]);
		rank3Digit = checkDigit(c->asRanking[2]);
		for (int i = 0;i < 3;i++) { ranking[i] = c->asRanking[i]; }

		if		(totalscore >= 900000)	{ rate = 'S'; }
		else if (totalscore >= 870000)	{ rate = 'A'; }
		else if (totalscore >= 800000)	{ rate = 'B'; }
		else							{ rate = 'C'; }

		break;
	case 3:
		if (totalscore > c->rkHiScore) {
			newrecord = TRUE;
			c->rkHiScore = totalscore;
		}
		for (int i = 0;i < 3;i++) {
			if (totalscore > c->rkRanking[i]) {
				rankIn = TRUE;
				rank = i + 1;
				for (int j = 2;j > i;j--) {
					c->rkRanking[j] = c->rkRanking[j - 1];
				}
				c->rkRanking[i] = totalscore;
				i = 100;								//更新したらブレイク
			}
		}
		rank1Digit = checkDigit(c->rkRanking[0]);
		rank2Digit = checkDigit(c->rkRanking[1]);
		rank3Digit = checkDigit(c->rkRanking[2]);
		for (int i = 0;i < 3;i++) { ranking[i] = c->rkRanking[i]; }

		if		(totalscore >= 800000) { rate = 'S'; }
		else if (totalscore >= 770000) { rate = 'A'; }
		else if (totalscore >= 650000) { rate = 'B'; }
		else						   { rate = 'C'; }

		break;
	default:
		break;
	}
	
	c->ScoreSave();
	mode = MODE::RESULTS;
}

GameClear::~GameClear()
{
	DeleteGraph(abcImage[0]);
	DeleteGraph(abcImage[1]);
	DeleteGraph(abcImage[2]);
	DeleteGraph(abcImage[3]);
	DeleteGraph(bgImage);
	DeleteGraph(scImage);
}

void GameClear::Update()
{
	Common* c = FindGameObject<Common>();
	Effects* e = FindGameObject<Effects>();

	switch (mode)
	{
	case MODE::RESULTS:
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
			if (GetMouseInput() & MOUSE_INPUT_LEFT) {
				changing = TRUE;
				mode = MODE::RANKING;
			}
		}
		break;

	case MODE::RANKING:
		if (x < Screen::WIDTH) { x += 50; }
		else { x = Screen::WIDTH; changing = FALSE; }

		if (e->Finished() && !changing) {
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
		break;
	default:
		break;
	}
}

void GameClear::Draw()
{
	Common* c = FindGameObject<Common>();
	Effects* e = FindGameObject<Effects>();

	//背景用
	DrawGraph(0, 0, bgImage, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 130);
	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawGraph(0, 0, scImage, TRUE);

	//数値幅取得用
	Width = GetDrawFormatStringWidthToHandle(c->textFont[1], "0");

	/*----------------------------------------------------------------------------------------------------------------------------------*/

	//SCORE
	DrawFormatStringToHandle(205 - x, 135, GetColor(0, 0, 0), c->textFont[0], "SCORE:");
	DrawFormatStringToHandle(200 - x, 130, GetColor(253, 163, 4), c->textFont[0], "SCORE:");
	for (int i = 0;i < 8 - scoreDigit;i++)
	{
		DrawFormatStringToHandle(210 - x + Width * i, 180, GetColor(0, 0, 0), c->textFont[1], "0");
		DrawFormatStringToHandle(200 - x + Width * i, 170, GetColor(150, 150, 150), c->textFont[1], "0");
	}
	DrawFormatStringToHandle(210 - x + Width * (8 - scoreDigit), 180, GetColor(0, 0, 0), c->textFont[1], "%d", c->score);
	DrawFormatStringToHandle(200 - x + Width * (8 - scoreDigit), 170, GetColor(255, 255, 255), c->textFont[1], "%d", c->score);

	//BREAK
	DrawFormatStringToHandle(205 - x, 285, GetColor(0, 0, 0), c->textFont[0], "BREAK:");
	DrawFormatStringToHandle(200 - x, 280, GetColor(253, 163, 4), c->textFont[0], "BREAK:");
	for (int i = 0;i < 8 - breakDigit;i++)
	{
		DrawFormatStringToHandle(210 - x + Width * i, 330, GetColor(0, 0, 0), c->textFont[1], "0");
		DrawFormatStringToHandle(200 - x + Width * i, 320, GetColor(150, 150, 150), c->textFont[1], "0");
	}
	DrawFormatStringToHandle(210 - x + Width * (8 - breakDigit), 330, GetColor(0, 0, 0), c->textFont[1], "%d", c->breakcount);
	DrawFormatStringToHandle(200 - x + Width * (8 - breakDigit), 320, GetColor(255, 255, 255), c->textFont[1], "%d", c->breakcount);

	//ランク用
	switch (rate)
	{
	case 'S':
		DrawGraph(700 - x, 130 + y, abcImage[0], TRUE);
		break;
	case 'A':
		DrawGraph(700 - x, 130 + y, abcImage[1], TRUE);
		break;
	case 'B':
		DrawGraph(700 - x, 130 + y, abcImage[2], TRUE);
		break;
	case 'C':
		DrawGraph(700 - x, 130 + y, abcImage[3], TRUE);
		break;
	default:
		break;
	}

	/*----------------------------------------------------------------------------------------------------------------------------------*/
	
	//1st
	rWidth = GetDrawFormatStringWidthToHandle(c->textFont[1], "1st");
	DrawFormatStringToHandle(340 + 70 - rWidth + Screen::WIDTH - x, 130, GetColor(0, 0, 0), c->textFont[1], "1st");
	DrawFormatStringToHandle(330 + 70 - rWidth + Screen::WIDTH - x, 120, GetColor(255, 215, 0), c->textFont[1], "1st");
	for (int i = 0;i < 8 - rank1Digit;i++)
	{
		DrawFormatStringToHandle(380 + 70 - x + Screen::WIDTH + Width * i, 130, GetColor(0, 0, 0), c->textFont[1], "0");
		DrawFormatStringToHandle(370 + 70 - x + Screen::WIDTH + Width * i, 120, GetColor(150, 150, 150), c->textFont[1], "0");
	}
	if (rank == 1) {
		e->setFlash(0.01);
		if (e->getFlash()) {
			DrawFormatStringToHandle(380 + 70 - x + Screen::WIDTH + Width * (8 - rank1Digit), 130, GetColor(0, 0, 0), c->textFont[1], "%d", ranking[0]);
			DrawFormatStringToHandle(370 + 70 - x + Screen::WIDTH + Width * (8 - rank1Digit), 120, GetColor(255, 0, 0), c->textFont[1], "%d", ranking[0]);
		}
		else {
			DrawFormatStringToHandle(380 + 70 - x + Screen::WIDTH + Width * (8 - rank1Digit), 130, GetColor(0, 0, 0), c->textFont[1], "%d", ranking[0]);
			DrawFormatStringToHandle(370 + 70 - x + Screen::WIDTH + Width * (8 - rank1Digit), 120, GetColor(255, 255, 0), c->textFont[1], "%d", ranking[0]);
		}
	}
	else {
		DrawFormatStringToHandle(380 + 70 - x + Screen::WIDTH + Width * (8 - rank1Digit), 130, GetColor(0, 0, 0), c->textFont[1], "%d", ranking[0]);
		DrawFormatStringToHandle(370 + 70 - x + Screen::WIDTH + Width * (8 - rank1Digit), 120, GetColor(255, 255, 255), c->textFont[1], "%d", ranking[0]);
	}
	

	//2nd
	rWidth = GetDrawFormatStringWidthToHandle(c->textFont[1], "2nd");
	DrawFormatStringToHandle(400 + 70 - rWidth + Screen::WIDTH - x, 230, GetColor(0, 0, 0), c->textFont[1], "2nd");
	DrawFormatStringToHandle(390 + 70 - rWidth + Screen::WIDTH - x, 220, GetColor(192, 192, 192), c->textFont[1], "2nd");
	for (int i = 0;i < 8 - rank2Digit;i++)
	{
		DrawFormatStringToHandle(440 + 70 - x + Screen::WIDTH + Width * i, 230, GetColor(0, 0, 0), c->textFont[1], "0");
		DrawFormatStringToHandle(430 + 70 - x + Screen::WIDTH + Width * i, 220, GetColor(150, 150, 150), c->textFont[1], "0");
	}
	if (rank == 2) {
		e->setFlash(0.01);
		if (e->getFlash()) {
			DrawFormatStringToHandle(440 + 70 + Screen::WIDTH - x + Width * (8 - rank2Digit), 230, GetColor(0, 0, 0), c->textFont[1], "%d", ranking[1]);
			DrawFormatStringToHandle(430 + 70 + Screen::WIDTH - x + Width * (8 - rank2Digit), 220, GetColor(255, 0, 0), c->textFont[1], "%d", ranking[1]);
		}
		else {
			DrawFormatStringToHandle(440 + 70 + Screen::WIDTH - x + Width * (8 - rank2Digit), 230, GetColor(0, 0, 0), c->textFont[1], "%d", ranking[1]);
			DrawFormatStringToHandle(430 + 70 + Screen::WIDTH - x + Width * (8 - rank2Digit), 220, GetColor(255, 255, 0), c->textFont[1], "%d", ranking[1]);
		}
	}
	else {
		DrawFormatStringToHandle(440 + 70 + Screen::WIDTH - x + Width * (8 - rank2Digit), 230, GetColor(0, 0, 0), c->textFont[1], "%d", ranking[1]);
		DrawFormatStringToHandle(430 + 70 + Screen::WIDTH - x + Width * (8 - rank2Digit), 220, GetColor(255, 255, 255), c->textFont[1], "%d", ranking[1]);
	}
	

	//3rd
	rWidth = GetDrawFormatStringWidthToHandle(c->textFont[1], "3rd");
	DrawFormatStringToHandle(450 + 70 - rWidth + Screen::WIDTH - x, 330, GetColor(0, 0, 0), c->textFont[1], "3rd");
	DrawFormatStringToHandle(440 + 70 - rWidth + Screen::WIDTH - x, 320, GetColor(196, 112, 34), c->textFont[1], "3rd");
	for (int i = 0;i < 8 - rank3Digit;i++)
	{
		DrawFormatStringToHandle(490 + 70 - x + Screen::WIDTH + Width * i, 330, GetColor(0, 0, 0), c->textFont[1], "0");
		DrawFormatStringToHandle(480 + 70 - x + Screen::WIDTH + Width * i, 320, GetColor(150, 150, 150), c->textFont[1], "0");
	}
	if (rank == 3) {
		e->setFlash(0.01);
		if (e->getFlash()) {
			DrawFormatStringToHandle(490 + 70 + Screen::WIDTH - x + Width * (8 - rank3Digit), 330, GetColor(0, 0, 0), c->textFont[1], "%d", ranking[2]);
			DrawFormatStringToHandle(480 + 70 + Screen::WIDTH - x + Width * (8 - rank3Digit), 320, GetColor(255, 0, 0), c->textFont[1], "%d", ranking[2]);
		}
		else {
			DrawFormatStringToHandle(490 + 70 + Screen::WIDTH - x + Width * (8 - rank3Digit), 330, GetColor(0, 0, 0), c->textFont[1], "%d", ranking[2]);
			DrawFormatStringToHandle(480 + 70 + Screen::WIDTH - x + Width * (8 - rank3Digit), 320, GetColor(255, 255, 0), c->textFont[1], "%d", ranking[2]);
		}
	}
	else {
		DrawFormatStringToHandle(490 + 70 + Screen::WIDTH - x + Width * (8 - rank3Digit), 330, GetColor(0, 0, 0), c->textFont[1], "%d", ranking[2]);
		DrawFormatStringToHandle(480 + 70 + Screen::WIDTH - x + Width * (8 - rank3Digit), 320, GetColor(255, 255, 255), c->textFont[1], "%d", ranking[2]);
	}
	

	/*----------------------------------------------------------------------------------------------------------------------------------*/

	//TOTAL
	DrawFormatStringToHandle(205, 475, GetColor(0, 0, 0), c->textFont[0], "TOTAL:");
	DrawFormatStringToHandle(200, 470, GetColor(253, 163, 4), c->textFont[0], "TOTAL:");
	if (newrecord) {
		DrawFormatStringToHandle(225, 525, GetColor(0, 0, 0), c->textFont[3], "NEW RECORD!!");
		DrawFormatStringToHandle(220, 520, GetColor(255, 255, 255), c->textFont[3], "NEW RECORD!!");
	}
	else if (rankIn) {
		DrawFormatStringToHandle(225, 525, GetColor(0, 0, 0), c->textFont[3], "RANK IN!");
		DrawFormatStringToHandle(220, 520, GetColor(255, 255, 255), c->textFont[3], "RANK IN!");
	}

	for (int i = 0;i < 8 - tScoreDigit;i++)
	{
		DrawFormatStringToHandle(410 + Width * i, 480, GetColor(0, 0, 0), c->textFont[1], "0");
		DrawFormatStringToHandle(400 + Width * i, 470, GetColor(150, 150, 150), c->textFont[1], "0");
	}
	if (rankIn) {
		e->setFlash(0.01);
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
		DrawLine(0, Screen::HEIGHT / 2, Screen::WIDTH, Screen::HEIGHT / 2, GetColor(0, 0, 255), 1);
		DrawLine(Screen::WIDTH / 2, 0, Screen::WIDTH / 2, Screen::HEIGHT, GetColor(0, 0, 255), 1);
	}
}

int GameClear::checkDigit(int num)
{
	int i = num;
	int digitCount = 1;
	while (i >= 9)
	{
		i /= 10;
		digitCount++;
	}
	return digitCount;
}
