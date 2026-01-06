#include "Select.h"
#include "Common.h"
#include "Effects.h"

Select::Select()
{
	bgImage = LoadGraph("data/image/Select_bg.png");
	wImage1 = LoadGraph("data/image/wepon/Gun.png");
	wImage2 = LoadGraph("data/image/wepon/Assault.png");
	wImage3 = LoadGraph("data/image/wepon/Rocket.png");

	wTitleFont = CreateFontToHandle("Agency FB", 100, -1, -1);
	wExplanaFont = CreateFontToHandle("Agency FB", 60, -1, -1);
	wExplanaFont2 = CreateFontToHandle("BIZ UDゴシック", 30, -1, -1);

	c1 = 1.0;
	c2 = 1.0;
	c3 = 1.0;
	nowSelect = 1;
}

Select::~Select()
{
	
}

void Select::Update()
{
	Common* c = FindGameObject<Common>();
	Effects* e = FindGameObject<Effects>();

	getUpdateKey();

	if (Key[KEY_INPUT_LEFT] == 1) {
		if (nowSelect > 1) {
			e->playSE("select");
			nowSelect--;
		}
	}
	if (Key[KEY_INPUT_RIGHT] == 1) {
		if (nowSelect < 3) {
			e->playSE("select");
			nowSelect++;
		}
	}
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		c->weponNum = nowSelect;
		e->playSE("define");
		e->FadeIn(0.5);
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_BACK)) {
		DestroyMe();
	}
}

void Select::Draw()
{
	DrawGraph(0, 0, bgImage, TRUE);
	DrawFormatString(0, 0, GetColor(0, 0, 0), "%d", nowSelect);

	switch (nowSelect)
	{
	case 1:
		DrawStringToHandle(0, 40, "Desert Eagle", GetColor(0, 0, 0), wTitleFont);
		DrawStringToHandle(5, 130, "Hand Gun", GetColor(0, 0, 0), wExplanaFont);
		DrawStringToHandle(5, 250, "火力の高い単発式のハンドガン。", GetColor(0, 0, 0), wExplanaFont2);
		DrawStringToHandle(5, 290, "リロードが素早く、取り回しが良い。", GetColor(0, 0, 0), wExplanaFont2);
		DrawStringToHandle(5, 370, "難易度 ★", GetColor(0, 0, 0), wExplanaFont2);
		DrawRotaGraph(930, 330, 1, 0.3, wImage1, TRUE);
		c1 = 1.2;
		c2 = 1.0;
		c3 = 1.0;
		break;

	case 2:
		DrawStringToHandle(0, 40, "AK-47", GetColor(0, 0, 0), wTitleFont);
		DrawStringToHandle(5, 130, "Assault Rifle", GetColor(0, 0, 0), wExplanaFont);
		DrawStringToHandle(5, 250, "弾数の多い連射式のライフル。", GetColor(0, 0, 0), wExplanaFont2);
		DrawStringToHandle(5, 290, "弾幕でゴリ押せ。", GetColor(0, 0, 0), wExplanaFont2);
		DrawStringToHandle(5, 370, "難易度 ★★", GetColor(0, 0, 0), wExplanaFont2);
		DrawRotaGraph(920, 320, 1, 0.3, wImage2, TRUE);
		c1 = 1.0;
		c2 = 1.2;
		c3 = 1.0;
		break;

	case 3: 
		DrawStringToHandle(0, 40, "ROCKTRUNCHERRRRRRRRRRRRRRRRRRRR", GetColor(0, 0, 0), wTitleFont);
		DrawStringToHandle(5, 130, "BOOOOM", GetColor(0, 0, 0), wExplanaFont);
		DrawStringToHandle(5, 290, "火力ゥ！", GetColor(0, 0, 0), wExplanaFont2);
		DrawStringToHandle(5, 370, "難易度 ★★★", GetColor(0, 0, 0), wExplanaFont2);
		DrawRotaGraph(920, 320, 0.8, 0.3, wImage3, TRUE);
		
		c1 = 1.0;
		c2 = 1.0;
		c3 = 1.2;
		break;

	default:
		break;
	}
	DrawRotaGraph(213, 581, 0.4 * c1, 0.4, wImage1, TRUE);
	DrawRotaGraph(500, 580, 0.35 * c2, 0.4, wImage2, TRUE);
	DrawRotaGraph(787, 581, 0.3 * c3, 0.4, wImage3, TRUE);
	
}

void Select::getUpdateKey()
{
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for (int i = 0;i < 256;i++) {
		if (tmpKey[i] != 0) {
			Key[i]++;
		}
		else{
			Key[i] = 0;
		}
	}
}
