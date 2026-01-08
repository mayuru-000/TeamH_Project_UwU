#include "Granade.h"
#include "Target.h"
#include "Effects.h"
#include <vector>

using namespace std;

Granade::Granade()
{
	exploImage = LoadGraph("data/Image/explode.png");
	GranadeImage = LoadGraph("data/Image/Granade.png");
}

Granade::~Granade()
{
}

void Granade::Update() {
	Effects* e = FindGameObject<Effects>();
	auto target = FindGameObjects<Target>();
	GetMousePoint(&x, &y);

	if (CheckHitKey(KEY_INPUT_Q)) {
		if (Gammo > 0 && !exploding) {
			for (auto t : target) {
				t->isHit(x, y, range, ammoDamage, num);
			}
			e->playSE("bomb", 200);
			Gammo -= 1;
			exploding = true;
			explTimer = 0;
			gx = x;
			gy = y;
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
	DrawString(0, 100, "GRANADE=", GetColor(255, 255, 255));
	DrawFormatString(75, 100, GetColor(255, 255, 255), "%d", Gammo);


	if (exploding) {
		DrawRectExtendGraph(gx - radius - 100, gy - radius - 100, gx + radius + 100, gy + radius + 100, 64 * (explTimer / 5), 0, 64, 64, exploImage, TRUE);
		DrawCircle(gx, gy, radius, GetColor(255, 0, 0), FALSE);
	}
}