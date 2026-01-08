#include "Clear.h"
#include "Common.h"
#include "Gunsetting.h"
#include "Field.h"
#include "Player.h"
#include "Screen.h"
#include "Effects.h"

using namespace std;

Clear::Clear()
{
	Common* c = FindGameObject<Common>();
	Gunsetting* Gset = FindGameObject<Gunsetting>();

	Gset->DestroyMe();

	bgImage = LoadGraph("data/image/bg/clear_bg.png");
	bufIcon = LoadGraph("data/image/icon/bufIcon.png");
	cardImage = LoadGraph("data/image/icon/card.png");
	bufBgImage = LoadGraph("data/image/icon/buf_bg.png");
	bufImage = LoadGraph("data/image/icon/buf_image.png");

	/*スコア登録*/
	c->hiScore == c->score;
	prevPush = FALSE;

	/*バフ選出*/
	buffs[0] = GetRand(5);
	do { buffs[1] = GetRand(5); } while (buffs[0] == buffs[1]);
	do { buffs[2] = GetRand(5); } while (buffs[0] == buffs[2] || buffs[1] == buffs[2]);
	
	sort(buffs, buffs + 3);

	/*バフ長さ取得*/
	count = 0;
	nowSelect =	1;
	for (int i = 0;i < size(c->mod);i++) { if (c->mod[i] >= 0) { count++; } }
}

Clear::~Clear()
{
}

void Clear::Update()
{
	Common* c = FindGameObject<Common>();
	Effects* e = FindGameObject<Effects>();
	Field* field = FindGameObject<Field>();

	if (CheckHitKey(KEY_INPUT_LEFT)) {
		if (prevPush) {
			if (nowSelect > 0) {
				e->playSE("select",255);
				nowSelect--;
				prevPush = FALSE;
			}
		}
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT)) {
		if (prevPush) {
			if (nowSelect < 2) {
				e->playSE("select", 255);
				nowSelect++;
				prevPush = FALSE;
			}
		}
	}
	else if (CheckHitKey(KEY_INPUT_R)) {
		if (prevPush) {
			if (nowSelect < 2) {
				buffs[0] = GetRand(5);
				do { buffs[1] = GetRand(5); } while (buffs[0] == buffs[1]);
				do { buffs[2] = GetRand(5); } while (buffs[0] == buffs[2] || buffs[1] == buffs[2]);

				sort(buffs, buffs + 3);
				prevPush = FALSE;
			}
		}
	}
	else {
		prevPush = TRUE;
	}

	if (CheckHitKey(KEY_INPUT_RETURN)) {
		c->mod[c->nowStage - 1] = buffs[nowSelect];
		if (c->nowStage < 5) {
			e->playSE("define", 255);
			selected();
		}
		
	}
}

void Clear::Draw()
{
	int buf1 = buffs[0];
	int buf2 = buffs[1];
	int buf3 = buffs[2];
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 90);
	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, GetColor(255, 255, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(0, 0, bgImage, TRUE);

	if (buf1 == 0 || buf1 == 3) { DrawRectGraph(180, 250, 0, 240 * 0, 240, 240, bufBgImage, TRUE); }
	else if (buf1 == 1 || buf1 == 4) { DrawRectGraph(180, 250, 0, 240 * 1, 240, 240, bufBgImage, TRUE); }
	else if (buf1 == 2 || buf1 == 5) { DrawRectGraph(180, 250, 0, 240 * 2, 240, 240, bufBgImage, TRUE); }
	if (buf2 == 0 || buf2 == 3) { DrawRectGraph(520, 250, 0, 240 * 0, 240, 240, bufBgImage, TRUE); }
	else if (buf2 == 1 || buf2 == 4) { DrawRectGraph(520, 250, 0, 240 * 1, 240, 240, bufBgImage, TRUE); }
	else if (buf2 == 2 || buf2 == 5) { DrawRectGraph(520, 250, 0, 240 * 2, 240, 240, bufBgImage, TRUE); }
	if (buf3 == 0 || buf3 == 3) { DrawRectGraph(860, 250, 0, 240 * 0, 240, 240, bufBgImage, TRUE); }
	else if (buf3 == 1 || buf3 == 4) { DrawRectGraph(860, 250, 0, 240 * 1, 240, 240, bufBgImage, TRUE); }
	else if (buf3 == 2 || buf3 == 5) { DrawRectGraph(860, 250, 0, 240 * 2, 240, 240, bufBgImage, TRUE); }

	DrawGraph(Screen::WIDTH / 2 - 515, 200, cardImage, TRUE);

	if (buf1 < 3) { DrawRectGraph(180, 250, 240 * 0, 240 * buf1, 240, 240, bufImage, TRUE); }
	else { DrawRectGraph(180, 250, 240 * 1, 240 * (buf1 - 3), 240, 240, bufImage, TRUE); }
	if (buf2 < 3) { DrawRectGraph(520, 250, 240 * 0, 240 * buf2, 240, 240, bufImage, TRUE); }
	else { DrawRectGraph(520, 250, 240 * 1, 240 * (buf2 - 3), 240, 240, bufImage, TRUE); }
	if (buf3 < 3) { DrawRectGraph(860, 250, 240 * 0, 240 * buf3, 240, 240, bufImage, TRUE); }
	else { DrawRectGraph(860, 250, 240 * 1, 240 * (buf3 - 3), 240, 240, bufImage, TRUE); }

	int widthB = 300;
	int heightB = 425;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	if (nowSelect == 0) 
	{
		DrawBox(150 + (widthB + 30) * 1, 220, 150 + widthB + (widthB + 45) * 1, 220 + heightB, GetColor(0, 0, 0), TRUE);
		DrawBox(150 + (widthB + 40) * 2, 220, 150 + widthB + (widthB + 40) * 2, 220 + heightB, GetColor(0, 0, 0), TRUE);
	}
	else if(nowSelect == 1)
	{
		DrawBox(150 + (widthB + 30) * 0, 220, 150 + widthB + (widthB + 30) * 0, 220 + heightB, GetColor(0, 0, 0), TRUE);
		DrawBox(150 + (widthB + 40) * 2, 220, 150 + widthB + (widthB + 40) * 2, 220 + heightB, GetColor(0, 0, 0), TRUE);
	}
	else if (nowSelect == 2)
	{
		DrawBox(150 + (widthB + 30) * 0, 220, 150 + widthB + (widthB + 30) * 0, 220 + heightB, GetColor(0, 0, 0), TRUE);
		DrawBox(150 + (widthB + 30) * 1, 220, 150 + widthB + (widthB + 45) * 1, 220 + heightB, GetColor(0, 0, 0), TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	DrawFormatString(0, 20, GetColor(0, 0, 0), "%d", nowSelect);

	Common* c = FindGameObject<Common>();
	int s = count;
	for (int i = 0;i < count;i++) {
		if (c->mod[i] < 3) { DrawRectGraph(Screen::WIDTH - 64 * s, 0, 64 * 0, 64 * c->mod[i], 64, 64, bufIcon, TRUE); }
		else if (c->mod[i] < 6) { DrawRectGraph(Screen::WIDTH - 64 * s, 0, 64 * 1, 64 * (c->mod[i] - 3), 64, 64, bufIcon, TRUE); }
		else if (c->mod[i] < 9) { DrawRectGraph(Screen::WIDTH - 64 * s, 0, 64 * 2, 64 * (c->mod[i] - 6), 64, 64, bufIcon, TRUE); }
		s--;
	}
}

void Clear::selected()
{
	Common* c = FindGameObject<Common>();
	Field* field = FindGameObject<Field>();
	Player* player = FindGameObject<Player>();

	if(c->nowStage!=0){ c->nowStage++; }		//デバッグ用

	field->DestroyMe();
	player->DestroyMe();

	new Field();
	new Gunsetting();
	new Player();

	DestroyMe();
}
