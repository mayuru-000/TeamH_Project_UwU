#include "Objects.h"
#include "Screen.h"

Objects::Objects()
{
	/*x = 2000;
	y = 310;
	scrollX = 6;

	char bgfile[60];
	sprintf_s<60>(bgfile, "data/image/objects/Obj_%d.png", 0);

	tImage = LoadGraph(bgfile);

	GetGraphSize(tImage, &tWIDTH, &tHEIGHT);*/
}

Objects::Objects(int fx, int fy, int handle, int speed)
{
	SetDrawOrder(0);
	x = fx;
	y = fy;
	scrollX = speed;

	char bgfile[60];
	sprintf_s<60>(bgfile, "data/image/objects/Obj_%d.png", handle);

	tImage = LoadGraph(bgfile);

	GetGraphSize(tImage, &tWIDTH, &tHEIGHT);
}

Objects::~Objects()
{
}

void Objects::Update()
{
	x -= scrollX;
	if (x + tWIDTH <= 0) { DestroyMe(); }
}

void Objects::Draw()
{
	DrawGraph(x, y, tImage, TRUE);
	DrawBox(x, y, x + tWIDTH, y + tHEIGHT, GetColor(255, 0, 0), FALSE);
}

bool Objects::isHitToObj(int px, int py)
{
	if ((x <= px && px <= x + tWIDTH) && (y <= py && py <= y + tHEIGHT))
	{
		return true;
	}
	return false;
}
