#include "Target.h"
#include "Objects.h"
#include "Common.h"
#include "Effects.h"
#include "Score.h"

Target::Target()
{
}

Target::Target(int fx, int fy, int handle, int fhp, int speed)
{
	Common* c = FindGameObject<Common>();

	dx = 0;
	dy = 0;
	hit = 0;
	deadCounter = 0;

	x = fx;
	y = fy;
	hp = fhp;
	maxhp = fhp;
	nam = handle;
	scrollX = speed;

	breaked = FALSE;

	char bgfile[60];
	sprintf_s<60>(bgfile, "data/image/target/Stage_%d/Target_%d.png",c->nowStage, handle);

	tImage = LoadGraph(bgfile);
	bmImage = LoadGraph("data/image/explosion.png");


	GetGraphSize(tImage, &tWIDTH, &tHEIGHT);
}

Target::~Target()
{
	DeleteGraph(tImage);
	DeleteGraph(bmImage);
}

void Target::Update()
{
	Common* c = FindGameObject<Common>();
	x -= scrollX;
	dx -= scrollX;

	if (breaked) {
		deadCounter++;
		if (deadCounter == 51) {
			c->breakcount++;
			DestroyMe();
		}
		return;
	}

	if (x + tWIDTH <= 0) { DestroyMe(); }
	if (hp <= 0) { breaked = TRUE; }
}

void Target::Draw()
{
	Common* c = FindGameObject<Common>();

	if (deadCounter == 0) {
		if (hit == 0) { DrawGraph(x, y, tImage, TRUE); }
		if (hit == 1) { DrawGraph(x + 15, y, tImage, TRUE); hit--; }
		if (hit == 2) { DrawGraph(x - 15, y, tImage, TRUE); hit--; }
	}
	else {
		//DrawGraph(x, y, tImage, TRUE);
		DrawRectExtendGraph(x-200, y- 200, x + tWIDTH+ 200, y + tHEIGHT+ 200, 64 * (deadCounter / 3), 0, 64, 64, bmImage, TRUE);
	}

	/*デバッグ用*/
	if (c->debugmode) {
		DrawFormatString(x, y - 20, GetColor(255, 255, 255), "HP::%d", hp);
		DrawBox(x, y, x + tWIDTH, y + tHEIGHT, GetColor(255, 0, 0), FALSE);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 60);
		DrawBox(x, y, x + tWIDTH, y + tHEIGHT, GetColor(255, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

bool Target::isHit(int px, int py, int r[], int dmg[], int num)
{ 
	Effects* e = FindGameObject<Effects>();
	Common* c = FindGameObject<Common>();
	Score* s = FindGameObject<Score>();

	if (!breaked) {
		for (int i = 0; i < num; i++) {
			if ((x - r[i] <= px && px <= x + tWIDTH + r[i]) && (y - r[i] <= py && py <= y + tHEIGHT + r[i]))
			{
				if ((x < px && px < x + tWIDTH) && (y < py && py < y + tHEIGHT)) { //中央ヒット
					if (hit == 0) { hit = 2; }

					if (hp - dmg[i] <= 0) { e->playSE("break", 200); }
					else { e->playSE("hit", 200); }
				}

				if (hp - dmg[i] <= 0) { 
					new Score(px, py, (float)maxhp * ((float)c->nowStage));
				}
				else{
					new Score(px, py, (float)maxhp * ((float)c->nowStage / 5.0));
				}
				hp -= dmg[i];
				return true;
			}
		}
	}

	return false;
}
