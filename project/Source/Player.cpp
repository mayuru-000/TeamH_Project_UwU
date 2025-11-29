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
		break;

	case 2:
		assault = new Assault();
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
