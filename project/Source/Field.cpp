#include "Field.h"
#include "Gun.h"
#include "Assault.h"
#include "Screen.h"
#include "Target.h"
#include <vector>

using namespace std;

vector<vector<int>> maps = {
	{300,500,700,900,1100,1300,1500,1700,1900},
	{100,100,100,100,100,100,100,100,100,},
	{00,00,00,00,00,00,00,00,00},
};

Field::Field()
{
	speedX = 5;
	scrollX = 0;

	char bgfile[60];
	sprintf_s<60>(bgfile, "data/image/field_bg_%d.jpg", 1);
	bgImage = LoadGraph(bgfile);
	GetGraphSize(bgImage, &ImageX, &ImageY);

	//fImage = LoadGraph("data/image/building_00.png");
	//GetGraphSize(fImage, &fImageX, &fImageY);

	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0;x < maps[y].size();x++) {
			new Target(maps[0][x], maps[1][x], maps[2][x],speedX);
		}
	}

}

Field::~Field()
{
}

void Field::Update()
{
	scrollX += speedX;
}

void Field::Draw()
{
	/*DrawExtendGraph(x, y, x + fImageX, y + fImageY, fImage, 1);

	DrawCircle(dx, dy, 10, GetColor(0, 255, 0), 1);
	DrawString(x, y - 20, "HP=", GetColor(255, 255, 255));
	DrawFormatString(x + 30, y - 20, GetColor(255, 255, 255), "%d", hp);*/

	DrawGraph(0 - scrollX, 0, bgImage, TRUE);
	DrawGraph(0 + ImageX - scrollX, 0, bgImage, TRUE);
	if (scrollX >= ImageX) {
		scrollX = 0;
	}
}

//bool Field::isHit(int px, int py, int dmg)
//{
//	dx = px;
//	dy = py;
//
//	if ((x <= dx && dx <= x + fImageX) && (y <= dy && dy <= y + fImageY)) {
//		hp -= dmg;
//		return true;
//	}
//	return false;
//}
