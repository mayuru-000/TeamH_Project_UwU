#include "BootScene.h"
#include "Common.h"
#include "Debug.h"
#include "Effects.h"

BootScene::BootScene()
{
	new Common();
	new Effects();
	//new Debug();
}

BootScene::~BootScene()
{
}

void BootScene::Update()
{
	SceneManager::ChangeScene("TITLE"); // ‹N“®‚ªI‚í‚Á‚½‚çTitle‚ğ•\¦
}

void BootScene::Draw()
{
}
