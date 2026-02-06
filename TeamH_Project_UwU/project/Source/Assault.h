#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "../Library/GameObject.h"

class Assault : public GameObject
{
public:
	Assault();
	Assault(float atk, float rate, float maxammo);
	~Assault();
	void Update() override;
	void Draw() override;

	void Reroad();
	float Deg2Rad(int dg) { return dg * (M_PI / 180.0); }

private:
	int weponImage;							//通常時のレティクル(青)
	int weponImage2;						//発砲時のレティクル(赤)

	int x, y;								//レティクル位置
	int ammo;								//残弾数
	int Maxammo;							//最大弾数

	int shotSpan;							//連射速度
	int spanCount;							//連射速度用カウント
	int reroadTime;							//リロード速度
	int startTime;							//リロード開始カウント

	float deg;								//打った後のレティクル回転状況(使わないかも)
	float Expansion;						//打った後のレティクル拡大状況(使わないかも)

	const float DegRate = 10.0;				//打った後のレティクル回転状況(使わないかも)
	const float ExpansionRate = 0.00025;	//打った後のレティクル拡大率　(使わないかも)

	static const int num = 3;				//中心からのHIT判定段階数
	int range[num] = { 10,30,50 };			//中心からのHIT判定距離
	int ammoDamage[num] = { 50,20,5 };		//HIT判定距離に応じた威力減衰

	bool shotcool = TRUE;					//打っていない状態
};
