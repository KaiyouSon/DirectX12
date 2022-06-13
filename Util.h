#pragma once
#include "Color.h"
#include "Random.h"
const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 720;
const int WIN_HALF_WIDTH = WIN_WIDTH / 2;
const int WIN_HALF_HEIGHT = WIN_HEIGHT / 2;

class Util
{
public:
	// ��r���đ傫������Ԃ�
	static float Max(float a, float b);

	// ��r���ď���������Ԃ�
	static float Min(float a, float b);

	// ������Ԃ��i -1, 0, 1 �j
	static int Sign(float a);
};