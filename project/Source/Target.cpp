#include "Target.h"

Target::Target()
{
	x = 0;
	y = 0;
	hitDmg = 0;
	hp = 100;
	scrollX = 0;
}

Target::Target(int fx, int fy, int handle, int fhp, int speed, bool rast)
{
	x = fx;
	y = fy;
	hp = fhp;
	scrollX = speed;

	rastobj = rast;
	breaked = FALSE;

	char bgfile[60];
	sprintf_s<60>(bgfile, "data/image/target/Target_%d.png", handle);

	tImage = LoadGraph(bgfile);
	bmImage = LoadGraph("data/image/explosion.png");

	GetGraphSize(tImage, &tWIDTH, &tHEIGHT);
}

Target::~Target()
{
	
}

void Target::Update()
{
	x -= scrollX;

	if ((x + tWIDTH <= 0) || (hp <= 0)) {
		DestroyMe();
	}
}

void Target::Draw()
{
	DrawGraph(x, y, tImage,TRUE);
	
	/*デバッグ用*/
	DrawFormatString(x, y - 20, GetColor(255, 255, 255), "HP::%d", hp);
	DrawBox(x, y, x + tWIDTH, y + tHEIGHT, GetColor(255, 0, 0), FALSE);
}

bool Target::isHit(int px, int py, int r[], int dmg[], int num)
{ 
	for (int i = 0; i < num; i++) {
		if ((x - r[i] <= px && px <= x + tWIDTH + r[i]) && (y - r[i] <= py && py <= y + tHEIGHT + r[i]))
		{
			hp -= dmg[i];
			return true;
		}
	}
	return false;
}
