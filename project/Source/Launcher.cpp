#include "Launcher.h"
#include "Target.h"
#include "Screen.h"
#include "Player.h"
#include "Effects.h"

Launcher::Launcher()
{
}

Launcher::Launcher(float atk, float rate, float maxammo)
{
	SetDrawOrder(-500);
	exploImage = LoadGraph("data/Image/explode.png");
	weponImage = LoadGraph("data/Image/player.png");
	weponImage2 = LoadGraph("data/Image/player_click.png");

	for (int i = 0; i < num; i++)
	{
		ammoDamage[num] *= ((atk + 100.0f) / 100.0f);
	}
	shotSpan = 1600 * ((100.0f - rate) / 100.0f);
	Maxammo = 3 * ((maxammo + 100.0f) / 100.0f);
	ammo = Maxammo;

	x = 0;
	y = 0;
	sx = 0;
	sy = 0;
	spanCount = 0;
	delayCount = 0;
	startTime = 0;
	Expansion = 0.15;
	reroadTime = shotSpan + 200;

	shotcool = TRUE;
	exploding = FALSE;
}

Launcher::~Launcher()
{
	DeleteGraph(exploImage);
	DeleteGraph(weponImage);
	DeleteGraph(weponImage2);
}

void Launcher::Update()
{
	Common* c = FindGameObject<Common>();
	Player* p = FindGameObject<Player>();
	Effects* e = FindGameObject<Effects>();

	GetMousePoint(&x, &y);

	if (!c->reroading) {

		if (delayCount != 0) {
			if (GetNowCount() - delayCount >= impactDelay) {
				delayCount = 0;
				exploding = TRUE;
				spanCount = GetNowCount();

				e->playSE("bomb", 255);
				auto target = FindGameObjects<Target>();
				for (auto t : target) {
					t->isHit(x, y, range, ammoDamage, num);
				}
				if (ammo == 0) {
					Reroad();
				}
			}
		}

		if (GetMouseInput() & MOUSE_INPUT_LEFT) {
			if (ammo > 0) {
				if ((GetNowCount() - spanCount >= shotSpan || ammo == Maxammo) && shotcool && delayCount == 0 && !exploding) {
					ammo -= 1;
					shotcool = FALSE;
					delayCount = GetNowCount();
					explTimer = 0;

					e->playSE("launcher", 255);
					//new Ammo(x, y, 20);
				}
			}
		}
		else
		{
			shotcool = TRUE;
		}

		if (CheckHitKey(KEY_INPUT_R)) {			//ƒŠƒ[ƒh
			Reroad();
		}
	}
	else
	{
		DrawString(0, 80, "REROADING...", GetColor(255, 255, 255));
		if (GetNowCount() - startTime >= reroadTime) {
			e->playSE("reroaded", 150);
			ammo = Maxammo;

			c->reroading = FALSE;
		}
	}

	if (exploding) {
		explTimer++;
		if (explTimer >= 21) {
			exploding = FALSE;
		}
	}
	p->AddGunData(ammo, Maxammo);
}

void Launcher::Draw()
{
	if (!shotcool || delayCount != 0) {
		DrawRotaGraph(x, y, Expansion, 0, weponImage2, TRUE, FALSE);
	}
	else
	{
		DrawRotaGraph(x, y, Expansion, 0, weponImage, TRUE, FALSE);
	}

	if (exploding) {
		DrawRectExtendGraph(x - range[num - 1] - 100, y - range[num - 1] - 100, x + range[num - 1] + 100, y + range[num - 1] + 100, 64 * (explTimer / 3), 0, 64, 64, exploImage, TRUE);
		DrawCircle(x, y, range[num - 1], GetColor(255, 0, 0), FALSE);
	}
}

void Launcher::Reroad()
{
	Common* c = FindGameObject<Common>();
	Effects* e = FindGameObject<Effects>();

	c->reroading = TRUE;
	e->playSE("reroading", 150);
	startTime = GetNowCount();
}
