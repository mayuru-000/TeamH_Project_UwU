#include "Player.h"
#include "Common.h"
#include "Gun.h"
#include "Assault.h"
#include "Granade.h"

using namespace std;

Player::Player()
{
	Common* c = FindGameObject<Common>();

	switch (c->weponNum)
	{
	case 1:
		gun = new Gun();
		granade = new Granade();
		break;

	case 2:
		assault = new Assault();
		granade = new Granade();
		break;

	default:
		SceneManager::ChangeScene("TITLE");
		break;
	}
}

Player::~Player()
{
}

void Player::Update()
{
}

void Player::Draw()
{
}

void Player::ChangeGun(int gunnum)
{
	
}
