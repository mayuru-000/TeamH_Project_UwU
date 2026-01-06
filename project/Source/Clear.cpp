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
	bufImage = LoadGraph("data/image/icon/bufIcon.png");

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
				e->playSE("select");
				nowSelect--;
				prevPush = FALSE;
			}
		}
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT)) {
		if (prevPush) {
			if (nowSelect < 2) {
				e->playSE("select");
				nowSelect++;
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
			e->playSE("define");
			selected();
		}
		
	}
}

void Clear::Draw()
{
	DrawGraph(0, 0, bgImage, TRUE);
	DrawFormatString(0, 20, GetColor(0, 0, 0), "%d", nowSelect);

	Common* c = FindGameObject<Common>();
	int s = count;
	for (int i = 0;i < count;i++) {
		if (c->mod[i] < 3) { DrawRectGraph(Screen::WIDTH - 64 * s, 0, 64 * 0, 64 * c->mod[i], 64, 64, bufImage, TRUE); }
		else if (c->mod[i] < 6) { DrawRectGraph(Screen::WIDTH - 64 * s, 0, 64 * 1, 64 * (c->mod[i] - 3), 64, 64, bufImage, TRUE); }
		else if (c->mod[i] < 9) { DrawRectGraph(Screen::WIDTH - 64 * s, 0, 64 * 2, 64 * (c->mod[i] - 6), 64, 64, bufImage, TRUE); }
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
