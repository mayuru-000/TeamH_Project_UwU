#include "Clear.h"
#include "Common.h"
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
	Player* player = FindGameObject<Player>();

	player->DestroyMe();

	bgImage = LoadGraph("data/image/bg/clear_bg.png");
	bufImage = LoadGraph("data/image/icon/bufIcon.png");

	c->hiScore += score;
	prevPush = FALSE;
}

Clear::~Clear()
{
}

void Clear::Update()
{
	Field* field = FindGameObject<Field>();
	Common* c = FindGameObject<Common>();


	if (CheckHitKey(KEY_INPUT_LEFT)) {
		if (!prevPush) {
			if (nowSelect > 1) {
				nowSelect--;
				prevPush = FALSE;
			}
		}
		prevPush = TRUE;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		if (!prevPush) {
			if (nowSelect < 3) {
				nowSelect++;
				prevPush = FALSE;
			}
		}
		prevPush = TRUE;
	}

	count = 0;
	for (int i = 0;i < size(c->mod);i++) { if (c->mod[i] >= 0) { count++; } }

	if (CheckHitKey(KEY_INPUT_RETURN)) {
		selected();
	}
}

void Clear::Draw()
{
	//DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, GetColor(255, 255, 255), TRUE);
	DrawGraph(0, 0, bgImage, TRUE);

	Common* c = FindGameObject<Common>();
	int s = count;
	for (int i = 0;i < count;i++) {

		DrawRectGraph(Screen::WIDTH - 64 * s, 0, 0, 64 * c->mod[i], 64, 64, bufImage, TRUE);
		s--;
	}
}

void Clear::selected()
{
	Field* field = FindGameObject<Field>();
	Common* c = FindGameObject<Common>();

	c->nowStage++;
	field->DestroyMe();

	new Field();
	new Player();

	DestroyMe();
}
