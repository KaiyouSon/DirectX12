#include "Random.h"
#include <math.h>
#include <stdlib.h>

Random random;

// int型の乱数を取得
int Random::Range(int min, int max)
{
	return rand() % ((max - min) + 1) + min;
}

// float型の乱数を取得
float Random::Range2(float min, float max)
{
	double tmp = (min < 0 && max>0) ? (fabs(min) + max) : (fabs(max - min));
	return (double)rand() / RAND_MAX * tmp + min;
}

// 確率でtrueを返す
bool Random::Bool(float rate)
{
	float num = Range2(0, 100);
	if (num < rate) return true;
	return false;
}