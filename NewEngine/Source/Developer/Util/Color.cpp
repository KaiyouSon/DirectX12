#include "NewEngine/Header/Developer/Util/Color.h"
#include "NewEngine/Header/Developer/Util/Util.h"

const Color Color::red(255, 0, 0);
const Color Color::green(0, 255, 0);
const Color Color::blue(0, 0, 255);
const Color Color::yellow(255, 255, 0);
const Color Color::white(255, 255, 255);
const Color Color::black(0, 0, 0);

//Color Color::SetRGB(float r, float g, float b)
//{
//	if (r > 255) r = 255;
//	if (g > 255) g = 255;
//	if (b > 255) b = 255;
//
//	if (r < 0) r = 0;
//	if (g < 0) g = 0;
//	if (b < 0) b = 0;
//
//	Color color;
//	color.r = r;
//	color.g = g;
//	color.b = b;
//
//	float max = Util::Max(Util::Max(r, g), b);
//	float min = Util::Min(Util::Min(r, g), b);
//
//	color.v = max / 256 * 100;
//
//	if (max == min)	color.h = 0, color.s = 0;
//	else
//	{
//		if (max == r) color.h = 60 * (g - b) / (max - min) + 0;
//		else if (max == g) color.h = 60.0 * (b - r) / (max - min) + 120.0;
//		else if (max == b) color.h = 60.0 * (r - g) / (max - min) + 240.0;
//
//		if (color.h > 360.0)  color.h = color.h - 360.0;
//		else if (color.h < 0) color.h = color.h + 360.0;
//		color.s = (max - min) / max * 100.0;
//	}
//
//	return color;
//}
//
//Color Color::SetHSV(float h, float s, float v)
//{
//	if (h > 360) h = 360;
//	if (s > 100) s = 100;
//	if (v > 100) v = 100;
//
//	if (h < 0) h = 0;
//	if (s < 0) s = 0;
//	if (v < 0) v = 0;
//
//	Color color;
//	color.h = h;
//	color.s = s;
//	color.v = v;
//
//	float max = v / 100 * 255;
//	float min = max - ((s / 100) * max);
//
//	if (h >= 0)
//	{
//		if (h <= 60)
//		{
//			color.r = max;
//			color.g = (h / 60) * (max - min) + min;
//			color.b = min;
//		}
//		else if (h <= 120)
//		{
//			color.r = ((120 - h) / 60) * (max - min) + min;
//			color.g = max;
//			color.b = min;
//		}
//		else if (h <= 180)
//		{
//			color.r = min;
//			color.g = max;
//			color.b = ((h - 120) / 60) * (max - min) + min;
//		}
//		else if (h <= 240)
//		{
//			color.r = min;
//			color.g = ((240 - h) / 60) * (max - min) + min;
//			color.b = max;
//		}
//		else if (h <= 300)
//		{
//			color.r = ((h - 240) / 60) * (max - min) + min;
//			color.g = min;
//			color.b = max;
//		}
//		else if (h <= 360)
//		{
//			color.r = max;
//			color.g = min;
//			color.b = ((360 - h) / 60) * (max - min) + min;
//		}
//	}
//
//	return color;
//}

bool Color::operator!=(const Color& other) const
{
	return r != other.r || g != other.g || b != other.b || a != other.a;
}
