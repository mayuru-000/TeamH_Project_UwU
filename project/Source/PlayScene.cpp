#include "PlayScene.h"
#include "TitleScene.h"
#include "Gunsetting.h"
#include "Player.h"
#include "Field.h"
#include "Effects.h"
#include "Clear.h"
#include "Common.h"
#include <DxLib.h>

PlayScene::PlayScene()
{
	new Field();
	new Gunsetting();
	new Player();

	prevPush = FALSE;
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	Common* c = FindGameObject<Common>();
	if (CheckHitKey(KEY_INPUT_TAB)) {
		if (!prevPush) {
			c->debugmode = !(c->debugmode);
			prevPush = TRUE;
		}
	}
	else {
		prevPush = FALSE;
	}

	if (CheckHitKey(KEY_INPUT_O)) {
		Field* field = FindGameObject<Field>();
		Player* player = FindGameObject<Player>();
		Gunsetting* gunset = FindGameObject<Gunsetting>();

		field ->DestroyMe();
		player->DestroyMe();
		if (!(field->getCleared())) { gunset->DestroyMe(); }
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
}
