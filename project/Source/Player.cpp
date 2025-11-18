#include "Player.h"
#include "Gun.h"
#include "Assault.h"
#include "Granade.h"

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
	//‚ ‚­‚Ü‚Å‰¼
	//Š®¬”Å‚ÍƒQ[ƒ€’†e‚Íˆê‚Â‚Ì‚İg—p
	if (CheckHitKey(KEY_INPUT_1)) {
		gunmode = 1;
	}
	if (CheckHitKey(KEY_INPUT_2)) {
		gunmode = 2;
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

		delete assault;
		gun = new Gun();
		break;

	case 2:
		gunflag = 2;

		delete gun;
		assault = new Assault();
		break;

	default:
		break;
	}
}
