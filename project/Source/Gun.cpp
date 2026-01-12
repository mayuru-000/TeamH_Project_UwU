#include "Gun.h"
#include "Target.h"
#include "Screen.h"
#include "Effects.h"

Gun::Gun()
{
	SetDrawOrder(-500);
	weponImage = LoadGraph("data/Image/player.png");
	weponImage2 = LoadGraph("data/Image/player_click.png");

	ammo = Maxammo;

	x = 640;
	y = 360;
	deg = 0.0;
	rad = 0.0;
	Expansion = 0.05;
}

Gun::~Gun()
{
	DeleteGraph(weponImage);
	DeleteGraph(weponImage2);
}

void Gun::Update()
{
	Effects* e = FindGameObject<Effects>();

	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);
	x += input.X / 100;
	y += input.Y / 100;
	if (GetJoypadNum() == 0) { GetMousePoint(&x, &y); }
	GetMousePoint(&x, &y);
	if (!reroading) {
		if (GetMouseInput() & MOUSE_INPUT_LEFT || input.Buttons[7] == 128)// 左クリックされたときの処理
		{
			if (ammo > 0) {
				if ((GetNowCount() - shotedSpan >= 400 || ammo == Maxammo) && shotcool == TRUE) {
					/*Expansion += ExpansionRate;
					if (Expansion > 0.3) {
						Expansion = 0.3;
					}*/
					ammo -= 1;
					shotcool = FALSE;
					shotedSpan = GetNowCount();

					e->playSE("gun", 255);

					auto target = FindGameObjects<Target>();
					for (auto t : target) {
						t->isHit(x, y, range, ammoDamage, num);
					}
				}
			}
			else
			{
				deg = 0.0;
				if (shotcool) {
					Reroad();
;				}
			}
		}
		else
		{
			/*Expansion -= ExpansionRate * 0.05;*/
			deg = 0.0;
			shotcool = TRUE;
			if (Expansion < 0.1) {
				Expansion = 0.1;
			}
		}

		if (CheckHitKey(KEY_INPUT_R)) {			//リロード
			Reroad();
		}
	}
	else
	{
		DrawString(0, 80, "REROADING...", GetColor(255, 255, 255));
		if (GetNowCount() - startTime >= 800) {
			e->playSE("reroaded", 150);
			ammo = Maxammo;
			reroading = FALSE;
		}
	}
}

void Gun::Draw()
{
	DrawString(0, 40, "GUNMODE_HANDGUN", GetColor(255, 255, 255));
	DrawString(0, 60, "AMMO=", GetColor(255, 255, 255));
	DrawFormatString(50, 60, GetColor(255, 255, 255), "%d", ammo);

	if (shotcool) {
		DrawRotaGraph(x, y, Expansion, Deg2Rad(deg), weponImage, TRUE, FALSE);
	}
	else
	{
		DrawRotaGraph(x, y, Expansion, Deg2Rad(deg), weponImage2, TRUE, FALSE);
		DrawLine(250, 500, x, y, GetColor(255, 255, 255), 5);
	}
	/*debug*/
	/*DrawCircle(x, y, range[0], GetColor(255, 255, 255), 0);
	DrawCircle(x, y, range[1], GetColor(255, 255, 255), 0);
	DrawCircle(x, y, range[2], GetColor(255, 255, 255), 0);*/
}

void Gun::Reroad() 
{
	Effects* e = FindGameObject<Effects>();

	reroading = TRUE;
	e->playSE("reroading", 150);
	startTime = GetNowCount();
}