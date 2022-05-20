#include "Random.h"
#include <math.h>
#include <stdlib.h>

// intŒ^‚Ì—”‚ğæ“¾
int Random::Range(int min, int max)
{
	return rand() % ((max - min) + 1) + min;
}

// floatŒ^‚Ì—”‚ğæ“¾
float Random::Range2(float min, float max)
{
	double tmp = (min < 0 && max>0) ? (fabs(min) + max) : (fabs(max - min));
	return (double)rand() / RAND_MAX * tmp + min;
}

// Šm—¦‚Åtrue‚ğ•Ô‚·
bool Random::Bool(float rate)
{
	float num = Range2(0, 100);
	if (num < rate) return true;
	return false;
}

Random& Random::GetInstance()
{
	static Random* random;
	return *random;
}
