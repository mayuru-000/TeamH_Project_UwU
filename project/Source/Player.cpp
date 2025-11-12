#include "Player.h"
#include "Gun.h"

using namespace std;

Player::Player()
{
	gun = new Gun();
}

Player::~Player()
{
}

void Player::Update()
{
	if (CheckHitKey(KEY_INPUT_1)) {
		gunmode = 1;
	}
	if (CheckHitKey(KEY_INPUT_2)) {
		gunmode = 2;
	}
	if (CheckHitKey(KEY_INPUT_3)) {
		gunmode = 3;
	}

	if (gunmode != gunflag) {
		ChangeGun(gunmode);
	}
	
}

void Player::Draw()
{
	
}



void Player::ChangeGun(int gunnum)
{
	switch (gunnum)
	{
	case 1:
		gunflag = 1;

		gun = new Gun();
		break;

	case 2:
		gunflag = 2;

		delete gun;
		gun = NULL;
		break;

	case 3:
		gunflag = 3;

		delete gun;
		gun = NULL;
		break;

	default:
		break;
	}
}
