#include "Gun.h"

Gun::Gun()
{
	gunImage = LoadGraph("data/Image/player.png");
	ammo = 100;
}

Gun::~Gun()
{
}

void Gun::Update()
{
	if (GetMouseInput() & MOUSE_INPUT_LEFT)	// ¶ƒNƒŠƒbƒN‚³‚ê‚½‚Æ‚«‚Ìˆ—
	{
		//new Gun();
		gunImage = LoadGraph("data/Image/player_click.png");
		Expansion += ExpansionRate;
		deg += 15;
		if (Expansion > 0.2) {
			Expansion = 0.2;
		}

	}
	else
	{
		gunImage = LoadGraph("data/Image/player.png");
		Expansion -= ExpansionRate * 5.0;
		deg = 0.0;
		if (Expansion < 0.1) {
			Expansion = 0.1;
		}
	}
}

void Gun::Draw()
{
	DrawString(0, 40, "GUNMODE_ASSAULT", GetColor(255, 255, 255));

	GetMousePoint(&x, &y);
	DrawRotaGraph(x, y, Expansion, Deg2Rad(deg), gunImage, TRUE, FALSE);
}
