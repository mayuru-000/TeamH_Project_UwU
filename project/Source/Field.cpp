#include "Field.h"
#include "Common.h"
#include "Screen.h"
#include "Target.h"
#include "Clear.h"
#include "Objects.h"
#include "CsvReader.h"
#include "Effects.h"
#include "GameClear.h"
#include "PlayScene.h"
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> maps;
vector<vector<int>> objMaps;

Field::Field()
{
	Common* c = FindGameObject<Common>();

	goalline = 0;
	scrollX = 0;
	objSpan_A = 250;
	objSpan_B = 250;
	objSponePoint_A = 0;
	objSponePoint_B = 0;
	sponed_A = FALSE;
	sponed_B = FALSE;
	cleared = FALSE;

	char filename[60];
	sprintf_s<60>(filename, "data/stage/Target/Stage_%d.csv", c->nowStage);
	CsvReader* csv = new CsvReader(filename);
	int lines = csv->GetLines(); // c‚Ìs”
	maps.resize(lines); // maps‚Ìs”‚ğcsv‚É‡‚í‚¹‚é
	for (int y = 0; y < lines; y++) {
		int cols = csv->GetColumns(y); // ‚»‚Ìs‚Ì‰¡‚Ì”
		maps[y].resize(cols); // maps[y]‚Ì—ñ”‚ğcsv‚É‡‚í‚¹‚é
		for (int x = 0; x < cols; x++) {
			int num = csv->GetInt(y, x);
			maps[y][x] = num;
		}
	}

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
		if (x == maps[1].size() - 1) { goalline = Max + blank + 700; }
		if (maps[2][x] != 0) { new Target(maps[0][x] + blank, maps[1][x], maps[2][x], maps[3][x], maps[4][x] + c->speedX); }
	}
}

Field::~Field()
{
	
}

void Field::Update()
{
	Effects* e = FindGameObject<Effects>();
	Common* c = FindGameObject<Common>();

	goalline -= c->speedX;
	scrollX += c->Speed("back");
	objSponePoint_A -= c->Speed("front");
	objSponePoint_B -= c->Speed("front");
	
	if (goalline <= 0 && !c->dontClear)
	{
		if (!cleared)
		{
			if (c->nowStage >= 9)
			{
				cleared = TRUE;
				c->cleared = TRUE;
				e->FadeOut(2);
				e->FadeOutBGM(2);
			}
			else
			{
				cleared = TRUE;
				c->cleared = TRUE;
				new Clear();
			}
		}
		else if (e->Finished() && c->nowStage >= 9)
		{
			new GameClear();
		}
	}
	if (goalline <= Screen::WIDTH)
	{
		return;
	}

	if (!sponed_A)
	{
		if ((Screen::WIDTH >= objSpan_A + objSponePoint_A) && (c->objPattern_A[c->nowStage - 1] != 0)) {
			if (GetRand(99) < 5) {
				sponed_A = TRUE;
				objSponePoint_A = Screen::WIDTH;
				new Objects("A");
			}
		}
	}
	if (!sponed_B) 
	{
		if ((Screen::WIDTH >= objSpan_B + objSponePoint_B) && (c->objPattern_B[c->nowStage - 1] != 0)) {
			if (GetRand(99) < 5) {
				sponed_B = TRUE;
				objSponePoint_B = Screen::WIDTH;
				new Objects("B");
			}
		}
	}
}

void Field::Draw()
{
	Common* c = FindGameObject<Common>();

	DrawGraph(0 - scrollX, 0, bgImage, TRUE);
	DrawGraph(0 + ImageX - scrollX, 0, bgImage, TRUE);
	if (scrollX >= ImageX) {
		scrollX = 0;
	}

	if (cleared) 
	{

	}

	/*debug*/
	if (c->debugmode) {
		DrawLine(goalline, 0, goalline, Screen::HEIGHT, GetColor(255, 255, 255), 1);
	}
}


