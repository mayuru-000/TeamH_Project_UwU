#include "Granade.h"
#include "Target.h"
#include "Effects.h"
#include "Field.h"
#include "Player.h"
#include "Common.h"
#include <vector>

using namespace std;

Granade::Granade()
{
}

Granade::Granade(float atkbuf, float rangebuf, float ammobuf)
{
	SetDrawOrder(-400);
	Common* c = FindGameObject<Common>();
	exploImage = LoadGraph("data/Image/explode.png");

	for (int i = 0; i < num; i++)
	{
		range[num] *= ((rangebuf + 100.0f) / 100.0f);
		ammoDamage[num] *= ((atkbuf + 100.0f) / 100.0f);
	}
	chargeSpeed = 75000 * ((100.0f - ammobuf) / 100.0f);
	MaxGAmmo = 3;

	if (c->nowStage == 1) { gAmmo = 1; }
	else	{ gAmmo = c->remGAmmo; }
	x = 0;
	y = 0;
	explTimer = 0;
	explDuration = 80;
	radius = range[num - 1];
}

Granade::~Granade()
{
	DeleteGraph(exploImage);
}

void Granade::Update() {
	Effects* e = FindGameObject<Effects>();
	Field* field = FindGameObject<Field>();
	Player* p = FindGameObject<Player>();
	Common* c = FindGameObject<Common>();
	auto target = FindGameObjects<Target>();
	GetMousePoint(&x, &y);

	if (field->cleared) {
		c->remGAmmo = gAmmo;
	}

	if (c->score - c->rastCharge >= chargeSpeed) {
		c->rastCharge = c->score;
		gAmmo++;
		if (gAmmo > MaxGAmmo) {
			gAmmo = MaxGAmmo;
		}
	}

	if (GetMouseInput() & MOUSE_INPUT_RIGHT) {
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
	p->AddGrData(gAmmo, MaxGAmmo);
}

void Granade::Draw() {
	// íeêîï\é¶
	//DrawFormatString(0, 60, GetColor(255, 255, 255), "GRANADE=%d", gAmmo);

	if (exploding) {
		DrawRectExtendGraph(x - radius - 100, y - radius - 100, x + radius + 100, y + radius + 100, 64 * (explTimer / 5), 0, 64, 64, exploImage, TRUE);
		//DrawCircle(x, y, radius, GetColor(255, 0, 0), FALSE);
	}
}