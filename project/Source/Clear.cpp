#include "Clear.h"
#include "Common.h"

Clear::Clear()
{
}

Clear::Clear(int score)
{
}

Clear::~Clear()
{
}

void Clear::Update()
{

	Common* c = FindGameObject<Common>();
	getUpdateKey();

	if (Key[KEY_INPUT_LEFT] == 1) {
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
		c->module[c->nowStage] = nowSelect;
	}
}

void Clear::Draw()
{

}

void Clear::getUpdateKey()
{
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) {
			Key[i]++;
		}
		else {
			Key[i] = 0;
		}
	}
}