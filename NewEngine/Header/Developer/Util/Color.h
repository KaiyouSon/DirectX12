#pragma once
class Color
{
public:
	float r, g, b;
	//float h, s, v;
	float a;

	constexpr Color() : r(255), g(255), b(255), a(255) {}
	constexpr Color(float r, float g, float b) : r(r), g(g), b(b), a(255) {}
	constexpr Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

	const static Color red;
	const static Color green;
	const static Color blue;
	const static Color yellow;
	const static Color white;
	const static Color black;

	//static Color SetRGB(float r, float g, float b);
	//static Color SetHSV(float h, float s, float v);
};

