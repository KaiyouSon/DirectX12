#pragma once
class Color
{
public:
	float r, g, b;
	float h, s, v;
	float a;
	Color();

	const static Color red;
	const static Color green;
	const static Color blue;
	const static Color yellow;
	const static Color white;
	const static Color black;

	static Color SetRGB(float r, float g, float b);
	static Color SetHSV(float h, float s, float v);
};

