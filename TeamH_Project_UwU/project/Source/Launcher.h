#pragma once
#include "../Library/GameObject.h"

class Launcher:public GameObject
{
public:
	Launcher();
	Launcher(float atk, float rate, float maxammo);
	~Launcher();
	void Update() override;
	void Draw() override;

	void Reroad();

private:
	int weponImage;								//通常時のレティクル(青)
	int weponImage2;							//発砲時のレティクル(赤)
	int exploImage;

	int x, y;									//レティクル位置
	int sx, sy;									//発射位置
	int ammo;									//残弾数
	int Maxammo;								//最大弾数

	int shotSpan;								//連射速度
	int spanCount;								//連射速度用カウント
	int reroadTime;								//リロード速度
	int startTime;								//リロード開始カウント
	const int impactDelay = 600;				//着弾までのディレイ
	int delayCount;								//ディレイ用カウント
	int explTimer;								//爆発中のカウント

	float Expansion;							//打った後のレティクル拡大状況(使わないかも)

	static const int num = 3;					//中心からのHIT判定段階数
	int range[num] = { 100,250,400 };			//中心からのHIT判定距離
	int ammoDamage[num] = { 500,300,200 };		//HIT判定距離に応じた威力減衰

	bool shotcool = TRUE;						//打っていない状態
	bool exploding = FALSE;						//爆発中の状態
};
