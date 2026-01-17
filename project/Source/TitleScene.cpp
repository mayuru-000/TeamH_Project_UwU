#include "TitleScene.h"
#include "Screen.h"
#include "Common.h"
#include "title.h"
#include "Effects.h"

TitleScene::TitleScene()
{
	new title();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void TitleScene::Draw()
{

}
