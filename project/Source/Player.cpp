#include "Player.h"
#include "Common.h"
#include "Gun.h"
#include "Assault.h"
#include "Granade.h"
#include "Screen.h"

using namespace std;

Player::Player()
{
	Common* c = FindGameObject<Common>();

	switch (c->weponNum)
	{
	case 1:
		gun = new Gun();
		break;

	case 2:
		assault = new Assault();
		break;

	default:
		SceneManager::ChangeScene("TITLE");
		break;
	}

	bufImage = LoadGraph("data/image/icon/bufIcon.png");
}

Player::~Player()
{
	delete gun;
	delete assault;
}

void Player::Update()
{
	count = 0;

	Common* c = FindGameObject<Common>();
	for (int i = 0;i < size(c->mod);i++) { if (c->mod[i] >= 0) { count++; } }
}

void Player::Draw()
{
	DrawRectGraph(Screen::WIDTH - 64 * count, 0, 0, 0, 64, 64, bufImage, TRUE);
}
