#define _CRT_SECURE_NO_WARNINGS
#include "Common.h"

Common::Common()
{
	DontDestroyOnSceneChange();
	ScoreLoad();

	remAmmo = 0;
	remGAmmo = 0;
	rastCharge = 0;
	weponNum = 0;

	score = 0;
	breakcount = 0;
	
	nowStage = 0;

	AddFontResourceExA("data/Font/POCKC___.TTF", FR_PRIVATE, NULL);
	textFont[0] = CreateFontToHandle("Pocket Calculator", 60, -1, -1);
	textFont[1] = CreateFontToHandle("Pocket Calculator", 125, -1, -1);
	textFont[2] = CreateFontToHandle("Pocket Calculator", 250, -1, -1);
	textFont[3] = CreateFontToHandle("Pocket Calculator", 30, -1, -1);

}

int Common::Speed(string mode)
{
	if (mode == "front") { return speedX + speedrange[nowStage - 1]; }
	if (mode == "back") { return speedX - speedrange[nowStage - 1]; }
	return 0;
}

void Common::ScoreLoad()
{
	FILE* gnFp = fopen("data/savedata/gnRanking.dat", "rb");
	FILE* asFp = fopen("data/savedata/asRanking.dat", "rb");
	FILE* rkFp = fopen("data/savedata/rkRanking.dat", "rb");

	if (gnFp != NULL) {
		fread(gnRanking, sizeof(int), 3, gnFp);
	}
	if (asFp != NULL) {
		fread(asRanking, sizeof(int), 3, asFp);
	}
	if (rkFp != NULL) {
		fread(rkRanking, sizeof(int), 3, rkFp);
	}

	gnHiScore = gnRanking[0];
	asHiScore = asRanking[0];
	rkHiScore = rkRanking[0];

	fclose(gnFp);
	fclose(asFp);
	fclose(rkFp);
}

void Common::ScoreSave()
{
	FILE* gnFp = fopen("data/savedata/gnRanking.dat", "wb");
	FILE* asFp = fopen("data/savedata/asRanking.dat", "wb");
	FILE* rkFp = fopen("data/savedata/rkRanking.dat", "wb");

	if (gnFp != NULL) {
		fwrite(gnRanking, sizeof(int), 3, gnFp);
	}
	if (asFp != NULL) {
		fwrite(asRanking, sizeof(int), 3, asFp);
	}
	if (rkFp != NULL) {
		fwrite(rkRanking, sizeof(int), 3, rkFp);
	}

	fclose(gnFp);
	fclose(asFp);
	fclose(rkFp);
}

void Common::Init()
{
	score = 0;
	remAmmo = 0;
	remGAmmo = 0;
	rastCharge = 0;
	weponNum = 0;
	breakcount = 0;
	nowStage = 1;

	reroading = FALSE;
	cleared = FALSE;
	gameCleared = FALSE;

	debugmode = FALSE;
	dontClear = FALSE;
	for (int i = 0;i < 9;i++) { mod[i] = -1; }
}
