#include "Target.h"

Target::Target()
{
	x = 0;
	y = 0;
	dx = 0;
	dy = 0;
	hitDmg = 0;
	hp = 100;
	scrollX = 0;
}

Target::Target(int fx, int fy,int handle,int speed)
{
	x = fx;
	y = fy;
	scrollX = speed;

	hp = 100;

	char bgfile[60];
	sprintf_s<60>(bgfile, "data/image/building_%02d.png", handle);
	tImage = LoadGraph(bgfile);
	GetGraphSize(tImage, &tWIDTH, &tHEIGHT);
}

Target::~Target()
{
}

void Target::Update()
{
	x -= scrollX;
	dx -= scrollX;

	if ((x + tWIDTH <= 0) || (hp <= 0)) {
		DestroyMe();
	}
}

void Target::Draw()
{
	DrawGraph(x, y, tImage,TRUE);

	/*デバッグ用*/
	DrawCircle(dx, dy, 100, GetColor(255, 0, 0), 1);
	DrawBox(x, y, x + tWIDTH, y + tHEIGHT, GetColor(255, 0, 0), FALSE);
}

bool Target::isHit(int px, int py, int damage)
{ 
	if ((x <= px && px <= x + tWIDTH) && (y <= py && py <= y + tHEIGHT)) {
		DestroyMe();
		return true;
	}
	return false;
}
