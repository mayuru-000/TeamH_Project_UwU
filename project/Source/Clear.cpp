#include "Clear.h"
#include "Common.h"
#include "Field.h"
#include "Player.h"

Clear::Clear()
{
}

Clear::Clear(int score)
{
	Common* c = FindGameObject<Common>();

	c->hiScore += score;
}

Clear::~Clear()
{
}

void Clear::Update()
{
	Field* field = FindGameObject<Field>();
	Common* c = FindGameObject<Common>();


	if (CheckHitKey(KEY_INPUT_LEFT)) {
		if (nowSelect > 1) {
			nowSelect--;
		}
	}
	if (Key[KEY_INPUT_RIGHT] == 1) {
		if (nowSelect < 3) {
			nowSelect++;
		}
	}
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		c->weponNum = nowSelect;
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_BACK)) {
		DestroyMe();
	}

	if (CheckHitKey(KEY_INPUT_RETURN)) {
		selected();
	}
}

void Clear::Draw()
{

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
