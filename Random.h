#pragma once
class Random
{
public:
	static int Range(int min, int max);			// int型の乱数を取得
	static float Range2(float min, float max);	// float型の乱数を取得
	static bool Bool(float rate); // 確率でtrueを返す

	static Random& GetInstance();
private:
	Random() = default;
	~Random() = default;

	Random(const Random&) = delete;
	Random& operator=(const Random&) = delete;
	Random(const Random&&) = delete;
	Random& operator=(const Random&&) = delete;
};