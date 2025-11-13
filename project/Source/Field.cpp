#include "Field.h"

Field::Field()
{
	fImage = LoadGraph("data/");
}

Field::~Field()
{
}

void Field::Update()
{
}

void Field::Draw()
{
}

bool Field::HitCheck(int px, int py)
{
	return false;
}
