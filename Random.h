#pragma once
class Random
{
public:
	static int Range(int min, int max);			// int�^�̗������擾
	static float Range2(float min, float max);	// float�^�̗������擾
	static bool Bool(float rate); // �m����true��Ԃ�

	static Random& GetInstance();
private:
	Random() = default;
	~Random() = default;

	Random(const Random&) = delete;
	Random& operator=(const Random&) = delete;
	Random(const Random&&) = delete;
	Random& operator=(const Random&&) = delete;
};