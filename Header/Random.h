#pragma once
class Random
{
public:
	static void Initialize();
	static int Range(int min, int max);			// intŒ^‚Ì—”‚ğæ“¾
	static float Range2(float min, float max);	// floatŒ^‚Ì—”‚ğæ“¾
	static bool Bool(float rate); // Šm—¦‚Åtrue‚ğ•Ô‚·

private:
	Random() = default;
	~Random() = default;

	Random(const Random&) = delete;
	Random& operator=(const Random&) = delete;
	Random(const Random&&) = delete;
	Random& operator=(const Random&&) = delete;
};