#include "Assault.h"
#include "Field.h"

Assault::Assault()
{
	weponSE = LoadSoundMem("data/Sound/SE/Assault.mp3");

	reroaro = LoadSoundMem("data/Sound/SE/reroaro.mp3");
	aroari = LoadSoundMem("data/Sound/SE/aroari.mp3");

	weponImage = LoadGraph("data/Image/player.png");
	ammo = Maxammo;
}

Assault::~Assault()
{
}

void Assault::Update()
{
	if (!reroading) {
		if (GetMouseInput() & MOUSE_INPUT_LEFT)	// 左クリックされたときの処理
		{
			if (ammo > 0) {
				weponImage = LoadGraph("data/Image/player_click.png");
				Expansion += ExpansionRate;
				shotcool = FALSE;
				deg += 15;
				if (Expansion > 0.2) {
					Expansion = 0.2;
				}

				if (count == 0)
				{
					ammo -= 1;
					PlaySoundMem(weponSE, DX_PLAYTYPE_BACK);
					count++;
				}
				else if (count >= 6)
				{
					count = 0;
				}
				else
				{
					count++;
				}
			}
			else
			{
				//弾切れ時の表示
				weponImage = LoadGraph("data/Image/player.png");
				deg = 0.0;
				if (shotcool) {
					Reroad();
				}
			}
		}
		else
		{
			weponImage = LoadGraph("data/Image/player.png");
			Expansion -= ExpansionRate * 5.0;
			shotcool = TRUE;
			deg = 0.0;
			count = 0;
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
		if (GetNowCount() - startTime >= 1800) {
			ammo = Maxammo;
			reroading = FALSE;
			ChangeNextPlayVolumeSoundMem(150, aroari);
			PlaySoundMem(aroari, DX_PLAYTYPE_BACK);
		}
	}
}

void Assault::Draw()
{
	DrawString(0, 40, "GUNMODE_ASSAULT", GetColor(255, 255, 255));
	DrawString(0, 60, "AMMO=", GetColor(255, 255, 255));
	DrawFormatString(50, 60, GetColor(255, 255, 255), "%d", ammo);

	GetMousePoint(&x, &y);
	DrawRotaGraph(x, y, Expansion, Deg2Rad(deg), weponImage, TRUE, FALSE);
}

void Assault::Reroad()
{
	reroading = TRUE;
	ChangeNextPlayVolumeSoundMem(150, reroaro);
	PlaySoundMem(reroaro, DX_PLAYTYPE_BACK);
	startTime = GetNowCount();
}