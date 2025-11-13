#include "TitleScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawString(100, 180, "Push [P]Key To Play", GetColor(255, 255, 255));
	DrawString(100, 200, "・1がハンドガン、2がアサルト", GetColor(255, 255, 255));
}
