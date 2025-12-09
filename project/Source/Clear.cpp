#include "Clear.h"
#include "Common.h"
#include "Gunsetting.h"
#include "Field.h"
#include "Player.h"
#include "Screen.h"

using namespace std;

string modlist[3] = { "attack","speed","bulletMaxnum" };

Clear::Clear()
{
}

Clear::Clear(int score)
{
	Common* c = FindGameObject<Common>();
	Gunsetting* Gset = FindGameObject<Gunsetting>();

	Gset->DestroyMe();

	bgImage = LoadGraph("data/image/bg/clear_bg.png");
	bufImage = LoadGraph("data/image/icon/bufIcon.png");

	c->hiScore += score;
	prevPush = FALSE;

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
	Field* field = FindGameObject<Field>();


	if (CheckHitKey(KEY_INPUT_LEFT)) {
		if (prevPush) {
			if (nowSelect > 1) {
				nowSelect--;
				prevPush = FALSE;
			}
		}
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT)) {
		if (prevPush) {
			if (nowSelect < 3) {
				nowSelect++;
				prevPush = FALSE;
			}
		}
	}
	else {
		prevPush = TRUE;
	}

	if (CheckHitKey(KEY_INPUT_RETURN)) {
		selected();
	}
}

void Clear::Draw()
{
	DrawGraph(0, 0, bgImage, TRUE);
	DrawFormatString(0, 20, GetColor(0, 0, 0), "%d", nowSelect);

	Common* c = FindGameObject<Common>();
	int s = count;
	for (int i = 0;i < count;i++) {
		if (i < 4) { DrawRectGraph(Screen::WIDTH - 64 * s, 0, 0, 64 * c->mod[i], 64, 64, bufImage, TRUE); }
		else if (i < 8) { DrawRectGraph(Screen::WIDTH - 64 * s, 0, 64 * 1, 64 * (c->mod[i] - 4), 64, 64, bufImage, TRUE); }
		else if (i < 12) { DrawRectGraph(Screen::WIDTH - 64 * s, 0, 64 * 2, 64 * (c->mod[i] - 8), 64, 64, bufImage, TRUE); }
		s--;
	}
}

void Clear::selected()
{
	Common* c = FindGameObject<Common>();
	Field* field = FindGameObject<Field>();
	Player* player = FindGameObject<Player>();

	if(c->nowStage!=-1){ c->nowStage++; }		//デバッグ用

	field->DestroyMe();
	player->DestroyMe();

	new Field();
	new Gunsetting();
	new Player();

	DestroyMe();
}
