#define _CRT_SECURE_NO_WARNINGS
#include "PlayScene.h"
#include "TitleScene.h"
#include "Gunsetting.h"
#include "Player.h"
#include "Field.h"
#include "Effects.h"
#include "Clear.h"
#include "GameClear.h"
#include "Common.h"
#include <DxLib.h>

PlayScene::PlayScene()
{
	Effects* e = FindGameObject<Effects>();
	e->playSE("BGM", 200);

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
	Effects* e = FindGameObject<Effects>();

	if (CheckHitKey(KEY_INPUT_TAB)) {
		if (!prevPush) {
			c->debugmode = !(c->debugmode);
			prevPush = TRUE;
		}
	}
	else if (CheckHitKey(KEY_INPUT_F1)) {
		if (!prevPush) {
			c->dontClear = !(c->dontClear);
			new GameClear();
			prevPush = TRUE;
		}
	}
	else {
		prevPush = FALSE;
	}

	if (CheckHitKey(KEY_INPUT_O)) {
		if (!c->gameCleared) {
			Field* field = FindGameObject<Field>();
			Player* player = FindGameObject<Player>();
			Gunsetting* gunset = FindGameObject<Gunsetting>();

			c->Init();
			c->cleared = FALSE;
			e->playSE("stopBGM", 0);

			field->DestroyMe();
			player->DestroyMe();
			if (!(field->cleared)) { gunset->DestroyMe(); }
			SceneManager::ChangeScene("TITLE");
		}
		else{
			c->Init();
			c->cleared = FALSE;
			e->playSE("stopBGM", 0);
			SceneManager::ChangeScene("TITLE");
		}
	}
	
	sprintf(stage, "STAGE_%d", c->nowStage);
}

void PlayScene::Draw()
{
	Common* c = FindGameObject<Common>();
	SetMainWindowText(stage);

	//DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
}
