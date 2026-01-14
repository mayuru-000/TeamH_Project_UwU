#include "Granade.h"
#include "Target.h"
#include "Effects.h"
#include "Common.h"
#include <vector>

using namespace std;

Granade::Granade()
{
}

Granade::Granade(float atkbuf, float rangebuf, float ammobuf)
{
	Common* c = FindGameObject<Common>();
	exploImage = LoadGraph("data/Image/explode.png");

	for (int i = 0; i < num; i++)
	{
		range[num] *= ((rangebuf + 100.0f) / 100.0f);
		ammoDamage[num] *= ((atkbuf + 100.0f) / 100.0f);
	}
	/*Ç±ÇÃï”óvëäík*/
	MaxGAmmo = 3 + ammobuf;
	if (c->nowStage == 1) { gAmmo = MaxGAmmo; }
	else	{ gAmmo = c->remGAmmo + ammobuf; }
	if (gAmmo > MaxGAmmo) { gAmmo = MaxGAmmo; }
	/*------------*/

	radius = range[num - 1];
	explDuration = 80;
}

Granade::~Granade()
{
}

void Granade::Update() {
	Effects* e = FindGameObject<Effects>();
	Common* c = FindGameObject<Common>();
	auto target = FindGameObjects<Target>();
	GetMousePoint(&x, &y);

	if (c->cleared) {
		c->remGAmmo = gAmmo;
	}

	if (CheckHitKey(KEY_INPUT_Q)) {
		if (gAmmo > 0 && !exploding) {
			for (auto t : target) {
				t->isHit(x, y, range, ammoDamage, num);
			}
			e->playSE("bomb", 200);
			gAmmo -= 1;
			exploding = true;
			explTimer = 0;
		}
	}

	if (exploding) {
		explTimer++;
		if (explTimer >= explDuration) {
			exploding = false;
		}
	}
}

void Granade::Draw() {
	// íeêîï\é¶
	DrawFormatString(0, 60, GetColor(255, 255, 255), "GRANADE=%d", gAmmo);

	if (exploding) {
		DrawRectExtendGraph(x - radius - 100, y - radius - 100, x + radius + 100, y + radius + 100, 64 * (explTimer / 5), 0, 64, 64, exploImage, TRUE);
		DrawCircle(x, y, radius, GetColor(255, 0, 0), FALSE);
	}
}