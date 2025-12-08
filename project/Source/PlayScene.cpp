#include "PlayScene.h"
#include "TitleScene.h"
#include "Gunsetting.h"
#include "Player.h"
#include "Field.h"
#include <DxLib.h>

PlayScene::PlayScene()
{
	new Field();
	new Gunsetting();
	new Player();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
}
