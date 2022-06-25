#pragma once
#include "NewEngine/Header/Developer/Util/Color.h"
#include "NewEngine/Header/Developer/Util/Random.h"

const int WIN_WIDTH = 1920;
const int WIN_HEIGHT = 1010;
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