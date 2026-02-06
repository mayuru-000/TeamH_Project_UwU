#pragma once
#include "../Library/GameObject.h"

class Objects:public GameObject
{
public:
	Objects();
	Objects(const char* mode);
	~Objects();
	void Update() override;
	void Draw() override;

	bool isHitToObj(int px, int py);
private:
	int tImage;
	int tWIDTH, tHEIGHT;

	int x, y;
	int scrollX;

	bool rastobj;
};