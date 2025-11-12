#include "Gun.h"
#include "Field.h"

Gun::Gun()
{
	gunSE = LoadSoundMem("data/Sound/SE/Gun.mp3");

	reroaro= LoadSoundMem("data/Sound/SE/reroaro.mp3");
	aroari= LoadSoundMem("data/Sound/SE/aroari.mp3");

	gunImage = LoadGraph("data/Image/player.png");
	ammo = Maxammo;
}

Gun::~Gun()
{
}

void Gun::Update()
{
	if (!reroading) {
		if (GetMouseInput() & MOUSE_INPUT_LEFT)	// 左クリックされたときの処理
		{
			if (ammo > 0) {
				if ((GetNowCount() - shotedSpan >= 400 || ammo == Maxammo) && shotcool == TRUE) {
					gunImage = LoadGraph("data/Image/player_click.png");
					Expansion += ExpansionRate;
					deg += 90;
					if (Expansion > 0.3) {
						Expansion = 0.3;
					}
					ammo -= 1;
					shotcool = FALSE;
					shotedSpan = GetNowCount();
					PlaySoundMem(gunSE, DX_PLAYTYPE_BACK);
				}
			}
			else
			{
				//弾切れ時の表示
				gunImage = LoadGraph("data/Image/player.png");
				deg = 0.0;
				if (shotcool) {
					Reroad();
;				}
			}
		}
		else
		{
			gunImage = LoadGraph("data/Image/player.png");
			Expansion -= ExpansionRate * 2.0;
			deg = 0.0;
			shotcool = TRUE;
			if (Expansion < 0.1) {
				Expansion = 0.1;
			}
		}

		if (CheckHitKey(KEY_INPUT_R)) {			//リロード
			Reroad();
		}
	}
	else
	{
		DrawString(0, 80, "REROADING...", GetColor(255, 255, 255));
		if (GetNowCount() - startTime >= 800) {
			ammo = Maxammo;
			reroading = FALSE;
			ChangeNextPlayVolumeSoundMem(150, aroari);
			PlaySoundMem(aroari, DX_PLAYTYPE_BACK);
		}
	}
}

void Gun::Draw()
{
	DrawString(0, 40, "GUNMODE_HANDGUN", GetColor(255, 255, 255));
	DrawString(0, 60, "AMMO=", GetColor(255, 255, 255));
	DrawFormatString(50, 60, GetColor(255, 255, 255), "%d", ammo);

	GetMousePoint(&x, &y);
	DrawRotaGraph(x, y, Expansion, Deg2Rad(deg), gunImage, TRUE, FALSE);
}

void Gun::Reroad() 
{
	reroading = TRUE;
	ChangeNextPlayVolumeSoundMem(150, reroaro);
	PlaySoundMem(reroaro, DX_PLAYTYPE_BACK);
	startTime = GetNowCount();
}