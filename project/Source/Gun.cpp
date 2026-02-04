#include "Gun.h"
#include "Target.h"
#include "Player.h"
#include "Ammo.h"
#include "Screen.h"
#include "Effects.h"
#include "Common.h"

Gun::Gun()
{
}

Gun::Gun(float atk, float rate, float maxammo)
{
	SetDrawOrder(-500);
	weponImage = LoadGraph("data/Image/player.png");
	weponImage2 = LoadGraph("data/Image/player_click.png");

	for (int i = 0; i < num; i++)
	{
		ammoDamage[num] *= ((atk + 100.0f) / 100.0f);
	}
	shotSpan = 400 * ((100.0f - rate) / 100.0f);
	Maxammo = 10 * ((maxammo + 100.0f) / 100.0f);
	ammo = Maxammo;

	x = 0;
	y = 0;
	deg = 0.0;
	Expansion = 0.1;
	reroadTime = 800;
}

Gun::~Gun()
{
	DeleteGraph(weponImage);
	DeleteGraph(weponImage2);
}

void Gun::Update()
{
	Common* c = FindGameObject<Common>();
	Player* p = FindGameObject<Player>();
	Effects* e = FindGameObject<Effects>();

	/*GetJoypadDirectInputState(DX_INPUT_PAD1, &input);
	x += input.X / 100;
	y += input.Y / 100;
	if (GetJoypadNum() == 0) { GetMousePoint(&x, &y); }*/
	GetMousePoint(&x, &y);
	if (!c->reroading) {
		if (GetMouseInput() & MOUSE_INPUT_LEFT)// 左クリックされたときの処理
		{
			if (ammo > 0) {
				deg += 20;
				if ((GetNowCount() - spanCount >= shotSpan || ammo == Maxammo) && shotcool == TRUE) {
					/*Expansion += ExpansionRate;
					if (Expansion > 0.3) {
						Expansion = 0.3;
					}*/
					ammo -= 1;
					shotcool = FALSE;
					spanCount = GetNowCount();

					e->playSE("gun", 255);
					new Ammo(x, y, 10);

					auto target = FindGameObjects<Target>();
					for (auto t : target) {
						t->isHit(x, y, range, ammoDamage, num);
					}
				}
			}
			else
			{
				deg = 0.0;
				Reroad();
			}
		}
		else
		{
			/*Expansion -= ExpansionRate * 0.05;*/
			deg = 0.0;
			shotcool = TRUE;
			/*if (Expansion < 0.1) {
				Expansion = 0.1;
			}*/
		}

		if (CheckHitKey(KEY_INPUT_R)) {			//リロード
			Reroad();
		}
	}
	else
	{
		DrawString(0, 80, "REROADING...", GetColor(255, 255, 255));
		if (GetNowCount() - startTime >= reroadTime) {
			e->playSE("reroaded", 255);
			ammo = Maxammo;
			
			c->reroading = FALSE;
		}
	}
	p->AddGunData(ammo, Maxammo);
}

void Gun::Draw()
{
	//DrawString(0, 20, "GUNMODE_HANDGUN", GetColor(255, 255, 255));

	if (shotcool) {
		DrawRotaGraph(x, y, Expansion, Deg2Rad(deg), weponImage, TRUE, FALSE);
	}
	else
	{
		DrawRotaGraph(x, y, Expansion, Deg2Rad(deg), weponImage2, TRUE, FALSE);
	}
	/*debug*/
	/*DrawCircle(x, y, range[0], GetColor(255, 255, 255), 0);
	DrawCircle(x, y, range[1], GetColor(255, 255, 255), 0);
	DrawCircle(x, y, range[2], GetColor(255, 255, 255), 0);*/
}

void Gun::Reroad() 
{
	Common* c = FindGameObject<Common>();
	Effects* e = FindGameObject<Effects>();

	c->reroading = TRUE;
	e->playSE("reroading", 255);
	startTime = GetNowCount();
}