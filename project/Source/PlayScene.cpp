#include "PlayScene.h"
#include "Player.h"
#include "Field.h"
#include <DxLib.h>

PlayScene::PlayScene()
{
	new Field();
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
