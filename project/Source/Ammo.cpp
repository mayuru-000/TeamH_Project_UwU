#include "Ammo.h"
#include "Screen.h"

Ammo::Ammo()
{
}

Ammo::Ammo(int px, int py, float sp)
{
	x = 150;
	y = 500;
	dx = px;
	dy = py;
	speed = sp;

	deltaX = (dx - x) / speed;
	deltaY = (dy - y) / speed;
	ammoImage = LoadGraph("");
}

Ammo::~Ammo()
{
}

void Ammo::Update()
{
	x += deltaX;
	y += deltaY;

	if ((x >= dx) || (y < dy)) {
		DestroyMe();
	}
}

void Ammo::Draw()
{
	DrawCircle(x, y, 15, GetColor(0, 227, 255), 1);
	DrawCircle(x, y, 12, GetColor(100, 155, 255), 1);
	DrawCircle(x, y, 10, GetColor(255, 255, 255), 1);
}
