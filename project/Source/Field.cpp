#include "Field.h"
#include "Common.h"
#include "Screen.h"
#include "Target.h"
#include "Clear.h"
#include "Objects.h"
#include "CsvReader.h"

#include <vector>

using namespace std;

vector<vector<int>> maps;

Field::Field()
{
	Common* c = FindGameObject<Common>();
	Objects* obj = FindGameObject<Objects>();

	goalline = 0;
	scrollX = 0;
	lastObj = FALSE;
	cleared = FALSE;


	char filename[60];
	sprintf_s<60>(filename, "data/stage/Stage_%d.csv", c->nowStage);
	// CSVから読んで、mapsを作る
	CsvReader* csv = new CsvReader(filename);
	int lines = csv->GetLines(); // 縦の行数
	maps.resize(lines); // mapsの行数をcsvに合わせる
	for (int y = 0; y < lines; y++) {
		int cols = csv->GetColumns(y); // その行の横の数
		maps[y].resize(cols); // maps[y]の列数をcsvに合わせる
		for (int x = 0; x < cols; x++) {
			int num = csv->GetInt(y, x);
			maps[y][x] = num;
		}
	}
	delete csv;

	char bgfile[60];
	sprintf_s<60>(bgfile, "data/image/bg/field_bg_%d.jpg", c->nowStage);
	bgImage = LoadGraph(bgfile);
	GetGraphSize(bgImage, &ImageX, &ImageY);

	int Max = 0;
	int Maxfast = 0;
	for (int x = 0;x < maps[0].size();x++) 
	{
		if (Max < maps[0][x]) { Max = maps[0][x]; }
		if (Maxfast < maps[4][x]) { Maxfast = maps[4][x]; }
		if (x == maps[1].size() - 1) { goalline = Max + 700; lastObj = TRUE; }
		else{ lastObj = FALSE; }
		if (maps[2][x] != 0) { new Target(maps[0][x], maps[1][x], maps[2][x], maps[3][x], maps[4][x] + c->speedX, lastObj); }
	}
	/*new Objects(2000, 310, 0, Maxfast + c->speedX + 1);
	new Objects(4500, 310, 0, Maxfast + c->speedX + 1);*/
}

Field::~Field()
{

}

void Field::Update()
{
	Common* c = FindGameObject<Common>();

	scrollX += c->speedX;
	goalline -= c->speedX;

	if (goalline < 0 && !cleared)
	{
		new Clear();
		cleared = TRUE;
	}
}

void Field::Draw()
{
	DrawGraph(0 - scrollX, 0, bgImage, TRUE);
	DrawGraph(0 + ImageX - scrollX, 0, bgImage, TRUE);
	if (scrollX >= ImageX) {
		scrollX = 0;
	}

	/*debug*/
	DrawLine(goalline, 0, goalline, Screen::HEIGHT, GetColor(255, 255, 255), 1);
}
