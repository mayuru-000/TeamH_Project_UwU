#include "Assault.h"
#include "Field.h"

Assault::Assault()
{
	weponSE = LoadSoundMem("data/Sound/SE/Assault.mp3");

	reroaro = LoadSoundMem("data/Sound/SE/reroaro.mp3");
	aroari = LoadSoundMem("data/Sound/SE/aroari.mp3");

	weponImage = LoadGraph("data/Image/player.png");
	weponImage2 = LoadGraph("data/Image/player_click.png");

	ammo = Maxammo;
	ammoDamage = 50;
}

Assault::~Assault()
{
	DeleteSoundMem(weponSE);
	DeleteSoundMem(reroaro);
	DeleteSoundMem(aroari);
}

void Assault::Update()
{
	GetMousePoint(&x, &y);
	if (!reroading) {
		if (GetMouseInput() & MOUSE_INPUT_LEFT)	// 左クリックされたときの処理
		{
			if (ammo > 0) {
				Expansion += ExpansionRate;
				shotcool = FALSE;
				deg += 10;
				if (Expansion > 0.15) {
					Expansion = 0.15;
				}

				if (count == 0)
				{
					ammo -= 1;
					PlaySoundMem(weponSE, DX_PLAYTYPE_BACK);

					Field* field = FindGameObject<Field>();
					field->isHit(x, y, ammoDamage);
					count++;
				}
				else if (count >= 7)
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
				deg = 0.0;
				if (shotcool) {
					Reroad();
				}
			}
		}
		else
		{
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

	if (shotcool) {
		DrawRotaGraph(x, y, Expansion, Deg2Rad(deg), weponImage, TRUE, FALSE);
	}
	else
	{
		DrawRotaGraph(x, y, Expansion, Deg2Rad(deg), weponImage2, TRUE, FALSE);
	}
}

void Assault::Reroad()
{
	reroading = TRUE;
	ChangeNextPlayVolumeSoundMem(150, reroaro);
	PlaySoundMem(reroaro, DX_PLAYTYPE_BACK);
	startTime = GetNowCount();
}