#pragma once
#include "NewEngine/Header/Developer/Util/Color.h"
#include "NewEngine/Header/Developer/Util/Random.h"
#include "NewEngine/Header/Developer/Util/Dirty.h"

const int WIN_WIDTH = 1920;
const int WIN_HEIGHT = 1010;
const int WIN_HALF_WIDTH = WIN_WIDTH / 2;
const int WIN_HALF_HEIGHT = WIN_HEIGHT / 2;

class Util
{
public:
	// 比較して大きい方を返す
	static float Max(float a, float b);

	// 比較して小さい方を返す
	static float Min(float a, float b);

	// 符号を返す（ -1, 0, 1 ）
	static int Sign(float a);
};