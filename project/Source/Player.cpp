#include "Player.h"
#include "Common.h"
#include "Granade.h"
#include "Screen.h"

using namespace std;

Player::Player()
{
	count = 0;
	bufSize = 0;
	flameCounter = 0;
	scrollX = 0;

	bufImage = LoadGraph("data/image/icon/bufIcon.png");
	carImage = LoadGraph("data/image/car.png");
	roadImage = LoadGraph("data/image/jimen.png");

	GetGraphSize(roadImage, &roadWIDTH, &roadHEIGHT);
	
	Common* c = FindGameObject<Common>();
	for (int i = 0;i < size(c->mod);i++) { if (c->mod[i] >= 0) { bufSize++; } }
}

Player::~Player()
{
}

void Player::Update()
{	
	Common* c = FindGameObject<Common>();

	flameCounter++;
	scrollX += c->speedX;

	if (flameCounter == 60) { flameCounter = 0; }

	count = flameCounter / 30;

	/**/

}

void Player::Draw()
{
	Common* c = FindGameObject<Common>();
	int s = bufSize;
	for (int i = 0;i < bufSize;i++) {
		if (i < 4) { DrawRectGraph(Screen::WIDTH - 64 * s, 0, 0, 64 * c->mod[i], 64, 64, bufImage, TRUE); }
		else if (i < 8) { DrawRectGraph(Screen::WIDTH - 64 * s, 0, 64 * 1, 64 * (c->mod[i] - 4), 64, 64, bufImage, TRUE); }
		else if (i < 12) { DrawRectGraph(Screen::WIDTH - 64 * s, 0, 64 * 2, 64 * (c->mod[i] - 8), 64, 64, bufImage, TRUE); }
		s--;
	}

	DrawGraph(0 - scrollX, Screen::HEIGHT - 170, roadImage, TRUE);
	DrawGraph(0 + roadWIDTH - scrollX, Screen::HEIGHT - 170, roadImage, TRUE);
	if (scrollX >= roadWIDTH) {
		scrollX = 0;
	}


	DrawRectGraph(30, Screen::HEIGHT - 330, 350 * count, 0, 350, 200, carImage, TRUE);
}
