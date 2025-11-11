#include "Player.h"

using namespace std;

Player::Player()
{
	pImage = LoadGraph("data/Image/player.png");
}

Player::~Player()
{
}

void Player::Update()
{
	
	if (GetMouseInput() & MOUSE_INPUT_LEFT)	// ¶ƒNƒŠƒbƒN‚³‚ê‚½‚Æ‚«‚Ìˆ—
	{
		//new Gun();
		pImage = LoadGraph("data/Image/player_click.png");
		Expansion += ExpansionRate;
		if (Expansion > 0.2) {
			Expansion = 0.2;
		}

	}
	else
	{
		pImage = LoadGraph("data/Image/player.png");
		Expansion -= ExpansionRate*2;
		if (Expansion < 0.1) {
			Expansion = 0.1;
		}
	}
}

void Player::Draw()
{
	GetMousePoint(&x, &y);
	DrawRotaGraph(x, y, Expansion, 0.0, pImage, TRUE, FALSE);
}