#include "Assault.h"
#include "Target.h"
#include "Screen.h"
#include "Player.h"
#include "Effects.h"

Assault::Assault()
{
}

Assault::Assault(float atk, float rate, float maxammo)
{
	SetDrawOrder(-500);
	weponImage = LoadGraph("data/Image/player.png");
	weponImage2 = LoadGraph("data/Image/player_click.png");

	for (int i = 0; i < num; i++)
	{
		ammoDamage[num] *= ((atk + 100.0f) / 100.0f);
	}
	shotSpan = 130 * ((100.0f - rate) / 100.0f);
	Maxammo = 30 * ((maxammo + 100.0f) / 100.0f);
	ammo = Maxammo;

	x = 0;
	y = 0;
	spanCount = 0;
	deg = 0.0;
	Expansion = 0.1;
	reroadTime = 1500;
}

Assault::~Assault()
{

}

void Assault::Update()
{
	Common* c = FindGameObject<Common>();
	Player* p = FindGameObject<Player>();
	Effects* e = FindGameObject<Effects>();

	GetMousePoint(&x, &y);
	if (!c->reroading) {
		if (GetMouseInput() & MOUSE_INPUT_LEFT)	// 左クリックされたときの処理
		{
			if (ammo > 0) {
				//Expansion += ExpansionRate;
				/*if (Expansion > 0.15) {
					Expansion = 0.15;
				}*/
				deg += 10;
				shotcool = FALSE;

				if (GetNowCount() - spanCount >= shotSpan || ammo == Maxammo)
				{
					ammo -= 1;
					e->playSE("assault", 255);
					
					auto target = FindGameObjects<Target>();
					for (auto t : target) {
						t->isHit(x, y, range, ammoDamage, num);
					}
					spanCount = GetNowCount();
				}
			}
			else
			{
				deg = 0.0;
				e->playSE("outAmmo",255);
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
			spanCount = 0;
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
			e->playSE("reroaded",150);
			ammo = Maxammo;
			c->reroading = FALSE;
		}
	}
	p->AddGunData(ammo, Maxammo);
}

void Assault::Draw()
{
	//DrawString(0, 20, "GUNMODE_ASSAULT", GetColor(255, 255, 255));

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
	Common* c = FindGameObject<Common>();
	Effects* e = FindGameObject<Effects>();
	e->playSE("reroading",150);
	c->reroading = TRUE;
	startTime = GetNowCount();
}