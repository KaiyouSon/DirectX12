#pragma once
class Color
{
public:
	float r, g, b, a;

	Color();
	Color(float r, float g, float b, float a);

	const static Color red;
	const static Color green;
	const static Color blue;
	const static Color yellow;
	const static Color white;
	const static Color black;
};

