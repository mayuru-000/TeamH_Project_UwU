#include "Field.h"
#include "Common.h"
#include "Gun.h"
#include "Assault.h"
#include "Screen.h"
#include "Target.h"
#include "Clear.h"
#include <vector>

using namespace std;

vector<vector<int>> maps = {
	{300,500,700,900,1100,1300,1500,1700,1900},
	{100,100,100,100,100,100,100,100,100,},
	{00,00,00,00,00,00,00,00,00},
};

Field::Field()
{
	score = 0;
	speedX = 10;
	scrollX = 0;

	cleared = FALSE;

	Common* c = FindGameObject<Common>();

	char bgfile[60];
	sprintf_s<60>(bgfile, "data/image/bg/field_bg_%d.jpg", c->nowStage);
	bgImage = LoadGraph(bgfile);
	GetGraphSize(bgImage, &ImageX, &ImageY);

	for (int x = 0;x < maps[1].size();x++) {
		new Target(maps[0][x], maps[1][x], maps[2][x], speedX);
		if (x == maps[1].size() - 1) { goalline = maps[0][x] + 700; }
	}
}

Field::~Field()
{
}

void Field::Update()
{
	Common* c = FindGameObject<Common>();

	scrollX += speedX;
	goalline -= speedX;

	if (goalline < 0 && !cleared)
	{
		new Clear(score);
		cleared = TRUE;
	}
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

	/*debug*/

	DrawLine(goalline, 0, goalline, Screen::HEIGHT, GetColor(255, 255, 255), 1);
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
