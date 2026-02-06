#include "Select.h"
#include "title.h"
#include "Common.h"
#include "Effects.h"
#include "Screen.h"

Select::Select()
{
	weponImage = LoadGraph("data/Image/player.png");
	bgImage = LoadGraph("data/image/Select_bg.png");
	wImage1 = LoadGraph("data/image/wepon/Gun.png");
	wImage2 = LoadGraph("data/image/wepon/Assault.png");
	wImage3 = LoadGraph("data/image/wepon/Rocket.png");
	tutorial1 = LoadGraph("data/image/tutorial_1.png");
	tutorial2 = LoadGraph("data/image/tutorial_2.png");
	bufImage = LoadGraph("data/image/icon/bufIcon.png");

	wTitleFont = CreateFontToHandle("Agency FB", 100, -1, -1);
	wExplanaFont = CreateFontToHandle("Agency FB", 60, -1, -1);
	wExplanaFont2 = CreateFontToHandle("BIZ UDゴシック", 30, -1, -1);

	x = 0;
	y = 0;
	c1 = 1.0;
	c2 = 1.0;
	c3 = 1.0;

	DeltaTime = 0.0f;
	Time = GetNowHiPerformanceCount();

	nowSelect = 2;
	mode = MODE::SELECT;
}

Select::~Select()
{
	DeleteGraph(weponImage);
	DeleteGraph(bgImage);
	DeleteGraph(wImage1);
	DeleteGraph(wImage2);
	DeleteGraph(wImage3);
	DeleteGraph(tutorial1);
	DeleteGraph(tutorial2);
	DeleteGraph(bufImage);

	DeleteFontToHandle(wTitleFont);
	DeleteFontToHandle(wExplanaFont);
	DeleteFontToHandle(wExplanaFont2);
}

void Select::Update()
{
	title* t = FindGameObject<title>();
	Common* c = FindGameObject<Common>();
	Effects* e = FindGameObject<Effects>();

	GetMousePoint(&x, &y);
	
	nowTime = GetNowHiPerformanceCount();
	DeltaTime = (nowTime - Time) / 1000000.0f;

	switch (mode)
	{
	case MODE::SELECT:
		if (e->Finished()) {
			if (check) {
				check = FALSE;
				mode = MODE::TUTORIAL_1;
				return;
			}

			if (100 <= x && x <= 340)
			{
				if (nowSelect != 1) {
					e->playSE("select", 300);
				}
				nowSelect = 1;
			}
			if (380 <= x && x <= 620)
			{
				if (nowSelect != 2) {
					e->playSE("select", 300);
				}
				nowSelect = 2;
			}
			if (660 <= x && x <= 900)
			{
				if (nowSelect != 3) {
					e->playSE("select", 300);
				}
				nowSelect = 3;
			}

			if ((GetMouseInput() & MOUSE_INPUT_LEFT) && !(t->prevPush)) {
				c->weponNum = nowSelect;
				e->playSE("define", 300);
				e->FadeOut(0.5);

				check = TRUE;
			}
		}
		
		break;

	case MODE::TUTORIAL_1:
		
		if (e->Finished()) 
		{
			if (DeltaTime >= 4.0f && check) {
				e->FadeOut(1);
				check = FALSE;
				mode = MODE::TUTORIAL_2;
			}
			else if (check) {
				return;
			}

			check = TRUE;
			Time = nowTime;
			e->FadeIn(0.5);
		}
		break;

	case MODE::TUTORIAL_2:

		if (e->Finished())
		{
			if (DeltaTime >= 4.0f && check) {
				e->FadeOut(0.5);
				SceneManager::ChangeScene("PLAY");
			}
			else if (check) {
				return;
			}

			check = TRUE;
			Time = nowTime;
			e->FadeIn(0.5);
		}
		break;

	default:
		break;
	}
	

	if (CheckHitKey(KEY_INPUT_BACK) || CheckHitKey(KEY_INPUT_O)) {
		DestroyMe();
	}
}

void Select::Draw()
{
	switch (mode)
	{
	case MODE::SELECT:
		DrawGraph(0, 0, bgImage, TRUE);
		switch (nowSelect)
		{
		case 1:
			DrawStringToHandle(0, 40, "Desert Eagle", GetColor(0, 0, 0), wTitleFont);
			DrawStringToHandle(5, 130, "Hand Gun", GetColor(0, 0, 0), wExplanaFont);
			DrawStringToHandle(5, 250, "火力の高い単発式のハンドガン。", GetColor(0, 0, 0), wExplanaFont2);
			DrawStringToHandle(5, 290, "リロードが素早く、取り回しが良い。", GetColor(0, 0, 0), wExplanaFont2);
			DrawStringToHandle(5, 370, "おすすめバフ：", GetColor(0, 0, 0), wExplanaFont2);
			DrawRectExtendGraph(220, 355, 220 + 64, 355 + 64, 64 * 0, 64 * 0, 64, 64, bufImage, 1);
			DrawRectExtendGraph(220 + (64 * 1), 355, 220 + (64 * 2), 355 + 64, 64 * 1, 64 * 1, 64, 64, bufImage, 1);
			DrawRectExtendGraph(220 + (64 * 2), 355, 220 + (64 * 3), 355 + 64, 64 * 1, 64 * 2, 64, 64, bufImage, 1);
			DrawRotaGraph(930, 330, 1, 0.3, wImage1, TRUE);

			c1 = 1.2;
			c2 = 1.0;
			c3 = 1.0;
			DrawRotaGraph(213, 581, 0.4 * c1, 0.4, wImage1, TRUE);
			DrawRotaGraph(500, 580, 0.35 * c2, 0.4, wImage2, TRUE);
			DrawRotaGraph(787, 581, 0.3 * c3, 0.4, wImage3, TRUE);
			break;

		case 2:
			DrawStringToHandle(0, 40, "AK-47", GetColor(0, 0, 0), wTitleFont);
			DrawStringToHandle(5, 130, "Assault Rifle", GetColor(0, 0, 0), wExplanaFont);
			DrawStringToHandle(5, 250, "弾数の多い連射式のライフル。", GetColor(0, 0, 0), wExplanaFont2);
			DrawStringToHandle(5, 290, "弾幕でゴリ押せ。", GetColor(0, 0, 0), wExplanaFont2);
			DrawStringToHandle(5, 370, "おすすめバフ：", GetColor(0, 0, 0), wExplanaFont2);
			DrawRectExtendGraph(220, 355, 220 + 64, 355 + 64, 64 * 0, 64 * 1, 64, 64, bufImage, 1);
			DrawRectExtendGraph(220 + (64 * 1), 355, 220 + (64 * 2), 355 + 64, 64 * 0, 64 * 2, 64, 64, bufImage, 1);
			//DrawRectExtendGraph(220 + (64 * 2), 355, 220 + (64 * 3), 355 + 64, 64 * 0, 64 * 0, 64, 64, bufImage, 1);
			DrawRotaGraph(920, 320, 1, 0.3, wImage2, TRUE);

			c1 = 1.0;
			c2 = 1.2;
			c3 = 1.0;
			DrawRotaGraph(213, 581, 0.4 * c1, 0.4, wImage1, TRUE);
			DrawRotaGraph(500, 580, 0.35 * c2, 0.4, wImage2, TRUE);
			DrawRotaGraph(787, 581, 0.3 * c3, 0.4, wImage3, TRUE);
			break;

		case 3:
			DrawStringToHandle(0, 40, "ROCKTRUNCHER", GetColor(0, 0, 0), wTitleFont);
			DrawStringToHandle(5, 130, "BOOOOM", GetColor(0, 0, 0), wExplanaFont);
			DrawStringToHandle(5, 290, "火力ゥ！", GetColor(0, 0, 0), wExplanaFont2);
			DrawStringToHandle(5, 370, "おすすめバフ：", GetColor(0, 0, 0), wExplanaFont2);
			DrawRectExtendGraph(220, 355, 220 + 64, 355 + 64, 64 * 0, 64 * 0, 64, 64, bufImage, 1);
			DrawRectExtendGraph(220 + (64 * 1), 355, 220 + (64 * 2), 355 + 64, 64 * 0, 64 * 1, 64, 64, bufImage, 1);
			//DrawRectExtendGraph(220 + (64 * 2), 355, 220 + (64 * 3), 355 + 64, 64 * 1, 64 * 2, 64, 64, bufImage, 1);
			DrawRotaGraph(920, 320, 0.8, 0.3, wImage3, TRUE);

			c1 = 1.0;
			c2 = 1.0;
			c3 = 1.2;
			DrawRotaGraph(213, 581, 0.4 * c1, 0.4, wImage1, TRUE);
			DrawRotaGraph(500, 580, 0.35 * c2, 0.4, wImage2, TRUE);
			DrawRotaGraph(787, 581, 0.3 * c3, 0.4, wImage3, TRUE);
			break;

		default:
			break;
		}
		break;

	case MODE::TUTORIAL_1:

		DrawGraph(0, 0, tutorial1, TRUE);
		//DrawStringToHandle(0, 40, "NOW LOADING...", GetColor(0, 0, 0), wTitleFont);
		break;

	case MODE::TUTORIAL_2:
		DrawGraph(0, 0, tutorial2, TRUE);
		//DrawStringToHandle(0, 40, "NOW LOADING...", GetColor(0, 0, 0), wTitleFont);
		break;

	default:
		break;
	}
	
	DrawRotaGraph(x, y, 0.1, 0, weponImage, TRUE, FALSE);

	/*DrawBox(100, 460, 340, 700, GetColor(255, 0, 0), TRUE);
	DrawBox(380, 460, 620, 700, GetColor(255, 0, 0), TRUE);
	DrawBox(660, 460, 900, 700, GetColor(255, 0, 0), TRUE);*/
}
