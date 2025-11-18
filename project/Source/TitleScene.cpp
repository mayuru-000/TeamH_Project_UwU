#include "TitleScene.h"

TitleScene::TitleScene()
{
	i = 0;
	inputMode = false;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	/*if (inputMode)
	{
		if (CheckHitKey(KEY_INPUT_1)) {
			i++;
			inputMode = false;
		}
		if (CheckHitKey(KEY_INPUT_2)) {
			i++;
			inputMode = false;
		}
	}*/
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

	/*switch (i)
	{
	case 0:
		DrawString(100, 50, "どの銃を使用しますか？　1:ピストル　2:ライフル", GetColor(255, 255, 255));
		inputMode = true;

	case 1:
		DrawString(100, 50, "？　1:　2:", GetColor(255, 255, 255));
		inputMode = true;

	case 2:
		DrawString(100, 50, "!　1:　2:", GetColor(255, 255, 255));
		inputMode = true;

	case 3:
		if (!inputMode) {
			SceneManager::ChangeScene("PLAY");
		}
		break;
	}*/
}
