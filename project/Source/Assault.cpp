#include "Assault.h"
#include "Target.h"
#include "Screen.h"
#include "Effects.h"

Assault::Assault()
{
	SetDrawOrder(-500);
	weponImage = LoadGraph("data/Image/player.png");
	weponImage2 = LoadGraph("data/Image/player_click.png");

	ammo = Maxammo;

	x = 0;
	y = 0;
	count = 0;
	deg = 0.0;
	rad = 0.0;
	Expansion = 0.05;
}

Assault::~Assault()
{

}

void Assault::Update()
{
	Effects* e = FindGameObject<Effects>();

	GetMousePoint(&x, &y);
	if (!reroading) {
		if (GetMouseInput() & MOUSE_INPUT_LEFT)	// 左クリックされたときの処理
		{
			if (ammo > 0) {
				//Expansion += ExpansionRate;
				shotcool = FALSE;
				deg += 10;
				/*if (Expansion > 0.15) {
					Expansion = 0.15;
				}*/

				if (count == 0)
				{
					ammo -= 1;
					e->playSE("assault", 255);
					
					auto target = FindGameObjects<Target>();
					for (auto t : target) {
						t->isHit(x, y, range, ammoDamage, num);
					}
					count++;
				}
				else if (count >= 7) { count = 0; }
				else { count++; }
			}
			else
			{
				deg = 0.0;
				if (shotcool) {
					Reroad();
				}
			}
		}
		else
		{
			/*Expansion -= ExpansionRate * 5.0;*/
			shotcool = TRUE;
			deg = 0.0;
			count = 0;
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
		if (GetNowCount() - startTime >= 1800) {
			e->playSE("reroaded",150);
			ammo = Maxammo;
			reroading = FALSE;
		}
	}
}

void Assault::Draw()
{
	DrawString(0, 40, "GUNMODE_ASSAULT", GetColor(255, 255, 255));
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
}

void Assault::Reroad()
{
	Effects* e = FindGameObject<Effects>();
	e->playSE("reroading",150);
	reroading = TRUE;
	startTime = GetNowCount();
}