#include "Target.h"

Target::Target()
{
	x = 0;
	y = 0;
	scrollX = 0;
}

Target::Target(int fx, int fy,int handle,int speed)
{
	x = fx;
	y = fy;
	scrollX = speed;

	char bgfile[60];
	sprintf_s<60>(bgfile, "data/image/building_%02d.png", 00);
	tImage = LoadGraph(bgfile);

}

Target::~Target()
{
}

void Target::Update()
{
	x -= scrollX;
}

void Target::Draw()
{
	DrawGraph(x, y, tImage,TRUE);
}

bool Target::isHit(int px, int py, int damage)
{
	return false;
}
