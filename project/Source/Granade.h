#pragma once
#include "../Library/GameObject.h"
#include "Common.h"

class Granade : public GameObject
{
private:
public:
	Common* c = FindGameObject<Common>();

	Granade();
	Granade(float atkbuf, float rangebuf, float ammobuf);
	~Granade();
	void Update() override;
	void Draw() override;

	int getGAmmo() { return gAmmo; }
	void setGAmmo() { c->remGAmmo = gAmmo; }
private:
	int exploImage;

	int x, y;									//レティクル位置
	int gAmmo;									//残弾数
	int MaxGAmmo;								//最大弾数

	int explDuration;							//連射速度
	int explTimer;								//連射速度用カウント
	int radius;									//最大爆発範囲
	int chargeSpeed;							//グレネードチャージスピード

	static const int num = 3;					//中心からのHIT判定段階数
	int range[num] = { 50,200,500 };			//中心からのHIT判定距離
	int ammoDamage[num] = { 600,300,100 };		//HIT判定距離に応じた威力減衰

	bool exploding = FALSE;						//打っていない状態
};

