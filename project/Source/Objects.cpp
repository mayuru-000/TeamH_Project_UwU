#include "Objects.h"
#include "Screen.h"
#include "Common.h"
#include "Field.h"

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

Objects::Objects(const char* mode)
{
	Common* c = FindGameObject<Common>();
	Field* f = FindGameObject<Field>();
	SetDrawOrder(0);

	
	scrollX = c->Speed("front");

	char bgfile[60];
	if (mode == "A") 
	{
		sprintf_s<60>(bgfile, "data/image/objects/Stage_%d/Obj_A_%d.png", c->nowStage, GetRand((c->objPattern_A[c->nowStage - 1]) - 1) + 1);
		tImage = LoadGraph(bgfile);
		GetGraphSize(tImage, &tWIDTH, &tHEIGHT);
		x = Screen::WIDTH;
		y = Screen::HEIGHT - 140 - tHEIGHT;
		f->addSpanA(tWIDTH);
		scrollX = c->Speed("front") + 10;
	} 
	else if(mode == "B")
	{
		sprintf_s<60>(bgfile, "data/image/objects/Stage_%d/Obj_B_%d.png", c->nowStage, GetRand((c->objPattern_B[c->nowStage - 1]) - 1) + 1);
		tImage = LoadGraph(bgfile);
		GetGraphSize(tImage, &tWIDTH, &tHEIGHT);
		x = Screen::WIDTH;
		y = 0;
		f->addSpanB(tWIDTH);
	}
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
	Common* c = FindGameObject<Common>();

	DrawGraph(x, y, tImage, TRUE);
	/*debug*/
	if (c->debugmode) {
		DrawBox(x, y, x + tWIDTH, y + tHEIGHT, GetColor(0, 0, 255), FALSE);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 60);
		DrawBox(x, y, x + tWIDTH, y + tHEIGHT, GetColor(0, 0, 255), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

bool Objects::isHitToObj(int px, int py)
{
	if ((x <= px && px <= x + tWIDTH) && (y <= py && py <= y + tHEIGHT))
	{
		return true;
	}
	return false;
}
