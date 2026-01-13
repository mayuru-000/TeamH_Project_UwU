#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "../Library/GameObject.h"

class Gun : public GameObject
{
public:
	Gun();
	Gun(float atk, float rate, float maxammo);
	~Gun();
	void Update() override;
	void Draw() override;

	void Reroad();
	float Deg2Rad(int dg) { return dg * (M_PI / 180.0); }

private:
	int weponImage;								//通常時のレティクル(青)
	int weponImage2;							//発砲時のレティクル(赤)

	int x, y;									//レティクル位置
	int ammo;									//残弾数
	int Maxammo;								//最大弾数

	int shotSpan;								//連射速度
	int spanCount;								//連射速度用カウント
	int reroadTime;								//リロード速度
	int startTime;								//リロード開始カウント

	float deg;									//打った後のレティクル回転状況
	float Expansion;							//打った後のレティクル拡大状況(使わないかも)

	const float ExpansionRate = 0.03;			//打った後のレティクル拡大率　(使わないかも)

	static const int num = 3;					//中心からのHIT判定段階数
	int range[num] = { 20,40,80 };				//中心からのHIT判定距離
	int ammoDamage[num] = { 150,50,10 };		//HIT判定距離に応じた威力減衰

	bool reroading = FALSE;						//リロード実行状態
	bool shotcool = TRUE;						//打っていない状態

	DINPUT_JOYSTATE input;						//コントローラー入力検知	(使うかも)
};
