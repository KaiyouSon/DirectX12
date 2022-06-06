#pragma once
#include "Color.h"
#include "Random.h"
const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 720;
const int WIN_HALF_WIDTH = WIN_WIDTH / 2;
const int WIN_HALF_HEIGHT = WIN_HEIGHT / 2;

// 比較して大きい方を返す
float Max(float a, float b);

// 比較して小さい方を返す
float Min(float a, float b);

// 符号を返す（ -1, 0, 1 ）
int Sign(float a);
