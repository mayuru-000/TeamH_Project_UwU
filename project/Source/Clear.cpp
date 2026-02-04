#include "Clear.h"
#include "Common.h"
#include "Granade.h"
#include "Gunsetting.h"
#include "Field.h"
#include "Player.h"
#include "Screen.h"
#include "Effects.h"

using namespace std;

Clear::Clear()
{
	Effects* e = FindGameObject<Effects>();
	Common* c = FindGameObject<Common>();
	Granade* g = FindGameObject<Granade>();
	Gunsetting* Gset = FindGameObject<Gunsetting>();
	SetDrawOrder(-1000);

	g->setGAmmo();
	Gset->DestroyMe();

	bgImage = LoadGraph("data/image/bg/clear_bg.png");
	bufIcon = LoadGraph("data/image/icon/bufIcon.png");
	cardImage = LoadGraph("data/image/icon/card.png");
	cardDImage_1 = LoadGraph("data/image/icon/card_1.png");
	cardDImage_2 = LoadGraph("data/image/icon/card_2.png");
	cardDImage_3 = LoadGraph("data/image/icon/card_3.png");

	bufBgImage = LoadGraph("data/image/icon/buf_bg.png");
	bufImage = LoadGraph("data/image/icon/buf_image.png");

	alpha = 0;
	prevPush = FALSE;
	selected = FALSE;

	/*バフ選出*/
	buffs[0] = GetRand(5);
	do { buffs[1] = GetRand(5); } while (buffs[0] == buffs[1]);
	do { buffs[2] = GetRand(5); } while (buffs[0] == buffs[2] || buffs[1] == buffs[2]);
	
	sort(buffs, buffs + 3);

	/*バフ長さ取得*/
	count = 0;
	nowSelect =	-1;
	for (int i = 0;i < size(c->mod);i++) { if (c->mod[i] >= 0) { count++; } }
}

Clear::~Clear()
{
	DeleteGraph(bgImage);
	DeleteGraph(bufIcon);
	DeleteGraph(cardImage);
	DeleteGraph(cardDImage_1);
	DeleteGraph(cardDImage_2);
	DeleteGraph(cardDImage_3);
	DeleteGraph(bufBgImage);
	DeleteGraph(bufImage);
}

void Clear::Update()
{
	Common* c = FindGameObject<Common>();
	Effects* e = FindGameObject<Effects>();
	Field* field = FindGameObject<Field>();
	Player* player = FindGameObject<Player>();
	GetMousePoint(&x, &y);
	if (alpha < 255) 
	{
		alpha += 5;
	}
	else
	{
		if (!selected)
		{
			if (144 <= x && x <= 461)
			{
				if (nowSelect != 0) {
					e->playSE("select", 300);
				}
				nowSelect = 0;
			}
			if (473 <= x && x <= 808)
			{
				if (nowSelect != 1) {
					e->playSE("select", 300);
				}
				nowSelect = 1;
			}
			if (828 <= x && x <= 1145)
			{
				if (nowSelect != 2) {
					e->playSE("select", 300);
				}
				nowSelect = 2;
			}

			if (GetMouseInput() & MOUSE_INPUT_LEFT) {
				c->mod[c->nowStage - 1] = buffs[nowSelect];
				if (c->nowStage < 9) {
					selected = TRUE;
					e->playSE("define", 255);
					e->FadeOut(2);
				}
			}
		}
		else
		{
			player->addX(10);
			if (e->Finished() && player->Finished()) { select(); }
		}
	}
}

void Clear::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	int buf1 = buffs[0];
	int buf2 = buffs[1];
	int buf3 = buffs[2];
	
	/*SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha - 95);
	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, GetColor(255, 255, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawGraph(0, 0, bgImage, TRUE);*/

	if (buf1 == 0 || buf1 == 3) { DrawRectGraph(180, 60, 0, 240 * 0, 240, 240, bufBgImage, TRUE); }
	else if (buf1 == 1 || buf1 == 4) { DrawRectGraph(180, 60, 0, 240 * 1, 240, 240, bufBgImage, TRUE); }
	else if (buf1 == 2 || buf1 == 5) { DrawRectGraph(180, 60, 0, 240 * 2, 240, 240, bufBgImage, TRUE); }
	if (buf2 == 0 || buf2 == 3) { DrawRectGraph(520, 60, 0, 240 * 0, 240, 240, bufBgImage, TRUE); }
	else if (buf2 == 1 || buf2 == 4) { DrawRectGraph(520, 60, 0, 240 * 1, 240, 240, bufBgImage, TRUE); }
	else if (buf2 == 2 || buf2 == 5) { DrawRectGraph(520, 60, 0, 240 * 2, 240, 240, bufBgImage, TRUE); }
	if (buf3 == 0 || buf3 == 3) { DrawRectGraph(860, 60, 0, 240 * 0, 240, 240, bufBgImage, TRUE); }
	else if (buf3 == 1 || buf3 == 4) { DrawRectGraph(860, 60, 0, 240 * 1, 240, 240, bufBgImage, TRUE); }
	else if (buf3 == 2 || buf3 == 5) { DrawRectGraph(860, 60, 0, 240 * 2, 240, 240, bufBgImage, TRUE); }

	DrawGraph(Screen::WIDTH / 2 - 515, 10, cardImage, TRUE);

	if (buf1 < 3) { DrawRectGraph(180, 60, 240 * 0, 240 * buf1, 240, 240, bufImage, TRUE); }
	else { DrawRectGraph(180, 60, 240 * 1, 240 * (buf1 - 3), 240, 240, bufImage, TRUE); }
	if (buf2 < 3) { DrawRectGraph(520, 60, 240 * 0, 240 * buf2, 240, 240, bufImage, TRUE); }
	else { DrawRectGraph(520, 60, 240 * 1, 240 * (buf2 - 3), 240, 240, bufImage, TRUE); }
	if (buf3 < 3) { DrawRectGraph(860, 60, 240 * 0, 240 * buf3, 240, 240, bufImage, TRUE); }
	else { DrawRectGraph(860, 60, 240 * 1, 240 * (buf3 - 3), 240, 240, bufImage, TRUE); }

	int widthB = 300;
	int heightB = 425;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha - 125);
	if (nowSelect == 0)
	{
		DrawGraph(Screen::WIDTH / 2 - 515 + 348, 10, cardDImage_2, TRUE);
		DrawGraph(Screen::WIDTH / 2 - 515 + 698, 10, cardDImage_3, TRUE);
	}
	else if(nowSelect == 1)
	{
		DrawGraph(Screen::WIDTH / 2 - 515 + 19,  10, cardDImage_1, TRUE);
		DrawGraph(Screen::WIDTH / 2 - 515 + 698, 10, cardDImage_3, TRUE);
	}
	else if (nowSelect == 2)
	{
		DrawGraph(Screen::WIDTH / 2 - 515 + 19,  10, cardDImage_1, TRUE);
		DrawGraph(Screen::WIDTH / 2 - 515 + 348, 10, cardDImage_2, TRUE);
	}
	else
	{
		DrawGraph(Screen::WIDTH / 2 - 515 +  19, 10, cardDImage_1, TRUE);
		DrawGraph(Screen::WIDTH / 2 - 515 + 348, 10, cardDImage_2, TRUE);
		DrawGraph(Screen::WIDTH / 2 - 515 + 698, 10, cardDImage_3, TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	//DrawFormatString(0, 20, GetColor(0, 0, 0), "%d", nowSelect);

	Common* c = FindGameObject<Common>();
	int s = count;
	for (int i = 0;i < count;i++) {
		if (c->mod[i] < 3) { DrawRectGraph(Screen::WIDTH - 64 * s, 0, 64 * 0, 64 * c->mod[i], 64, 64, bufIcon, TRUE); }
		else if (c->mod[i] < 6) { DrawRectGraph(Screen::WIDTH - 64 * s, 0, 64 * 1, 64 * (c->mod[i] - 3), 64, 64, bufIcon, TRUE); }
		else if (c->mod[i] < 9) { DrawRectGraph(Screen::WIDTH - 64 * s, 0, 64 * 2, 64 * (c->mod[i] - 6), 64, 64, bufIcon, TRUE); }
		s--;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Clear::select()
{
	Effects* e = FindGameObject<Effects>();
	Common* c = FindGameObject<Common>();
	Field* field = FindGameObject<Field>();
	Player* player = FindGameObject<Player>();

	if(c->nowStage!=0){ c->nowStage++; }		//デバッグ用

	c->cleared = FALSE;
	field->DestroyMe();
	player->DestroyMe();

	new Field();
	new Gunsetting();
	new Player();

	e->playSE("trans", 255);
	e->FadeIn(0.5);

	DestroyMe();
}
