#pragma once
class Random
{
public:
	static void Initialize();
	static int Range(int min, int max);			// int�^�̗������擾
	static float Range2(float min, float max);	// float�^�̗������擾
	static bool Bool(float rate); // �m����true��Ԃ�
};