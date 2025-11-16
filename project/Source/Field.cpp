#include "Field.h"
#include "Gun.h"
#include "Assault.h"

Field::Field()
{
	fImage = LoadGraph("data/");
	x = 0;
	y = 0;
}

Field::~Field()
{
}

void Field::Update()
{
}

void Field::Draw()
{
	DrawCircle(x, y, 10, GetColor(255, 255, 255), 1);
}

bool Field::isHit(int px, int py)
{
	//“–‚½‚è”»’è‚Ì•\Ž¦
	x = px;
	y = py;
	return false;
}
