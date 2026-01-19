#include "Gunsetting.h"
#include "Common.h"
#include "Gun.h"
#include "Assault.h"
#include "Granade.h"

Gunsetting::Gunsetting()
{
	Common* c = FindGameObject<Common>();

	atkBuf = 0;
	rateBuf = 0;
	maxammoBuf = 0;
	bomAtkBuf = 0;
	bomRangeBuf = 0;
	bomAmmoBuf = 0;

	for (int i = 0;(c->mod[i] != -1) && (i < 9);i++) 
	{
		switch (c->mod[i]) {
		case 0:
			atkBuf += 30.0f;
			break;
		case 1:
			rateBuf += 10.0f;
			break;
		case 2:
			maxammoBuf += 20.0f;
			break;
		case 3:
			bomAtkBuf += 20.0f;
			break;
		case 4:
			bomRangeBuf += 10.0f;
			break;
		case 5:
			bomAmmoBuf += 1;
			break;
		}
	}

	switch (c->weponNum)
	{
	case 1:
		gun = new Gun(atkBuf, rateBuf, maxammoBuf);
		granade = new Granade(bomAtkBuf, bomRangeBuf, bomAmmoBuf);
		break;

	case 2:
		assault = new Assault(atkBuf, rateBuf, maxammoBuf);
		granade = new Granade(bomAtkBuf, bomRangeBuf, bomAmmoBuf);
		break;

	case 3:
		launcher = new Launcher(atkBuf, rateBuf, maxammoBuf);
		granade = new Granade(bomAtkBuf, bomRangeBuf, bomAmmoBuf);
		break;

	default:
		SceneManager::ChangeScene("TITLE");
		break;
	}
}

Gunsetting::~Gunsetting()
{
	delete gun;
	delete assault;
	delete granade;
	delete launcher;
}
