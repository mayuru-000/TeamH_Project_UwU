#include "Field.h"
#include "Gun.h"
#include "Assault.h"
#include <vector>

using namespace std;

vector<vector<int>> maps;

char field_X[255];
char field_Y[255];
char field_Img[255];

Field::Field()
{
	fImage = LoadGraph("data/image/building_00.png");
	GetGraphSize(fImage, &fImageX, &fImageY);

	dx = -100;
	dy = -100;

	hp = 1000;
}

Field::~Field()
{
}

void Field::Update()
{
	x = 500;
	y = 200;
}

void Field::Draw()
{
	DrawExtendGraph(x, y, x + fImageX, y + fImageY, fImage, 1);

	DrawCircle(dx, dy, 10, GetColor(0, 255, 0), 1);

	DrawString(x, y - 20, "HP=", GetColor(255, 255, 255));
	DrawFormatString(x + 30, y - 20, GetColor(255, 255, 255), "%d", hp);
	
}

bool Field::isHit(int px, int py, int dmg)
{
	dx = px;
	dy = py;

	if ((x <= dx && dx <= x + fImageX) && (y <= dy && dy <= y + fImageY)) {
		hp -= dmg;
		return true;
	}
	return false;
}
