#include "Player.h"
#include "Common.h"
#include "Granade.h"
#include "Screen.h"

using namespace std;

Player::Player()
{
	Common* c = FindGameObject<Common>();

	count = 0;
	bufSize = 0;
	flameCounter = 0;
	scrollX = 0;
	nowSelect = 0;

	bufImage = LoadGraph("data/image/icon/bufIcon.png");
	carImage = LoadGraph("data/image/car.png");

	char bgfile[60];
	sprintf_s<60>(bgfile, "data/image/road/road_%d.png", c->nowStage);
	roadImage = LoadGraph(bgfile);
	GetGraphSize(roadImage, &roadWIDTH, &roadHEIGHT);
	
	for (int i = 0;i < 10;i++) { if (c->mod[i] >= 0) { bufSize++; } }
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
	/*if (CheckHitKey(KEY_INPUT_LEFT)) {
		if (prevPush) {
			nowSelect--;
			prevPush = FALSE;
		}
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT)) {
		if (prevPush) {
			nowSelect++;
			prevPush = FALSE;
		}
	}
	else {
		prevPush = TRUE;
	}*/
}

void Player::Draw()
{
	SetDrawOrder(0);
	Common* c = FindGameObject<Common>();

	DrawGraph(0 - scrollX, Screen::HEIGHT - roadHEIGHT, roadImage, TRUE);
	DrawGraph(0 + roadWIDTH - scrollX, Screen::HEIGHT - roadHEIGHT, roadImage, TRUE);
	if (scrollX >= roadWIDTH) {
		scrollX = 0;
	}


	DrawRectGraph(30, Screen::HEIGHT - 300, 350 * count, 0, 350, 200, carImage, TRUE);

	int s = bufSize;
	for (int i = 0;i < bufSize;i++) {
		if (c->mod[i] < 3)		{ DrawRectGraph(Screen::WIDTH - 64 * s, 0, 64 * 0, 64 * c->mod[i], 64, 64, bufImage, TRUE); }
		else if (c->mod[i] < 6) { DrawRectGraph(Screen::WIDTH - 64 * s, 0, 64 * 1, 64 * (c->mod[i] - 3), 64, 64, bufImage, TRUE); }
		else if (c->mod[i] < 9) { DrawRectGraph(Screen::WIDTH - 64 * s, 0, 64 * 2, 64 * (c->mod[i] - 6), 64, 64, bufImage, TRUE); }
		s--;
	}

	
}
