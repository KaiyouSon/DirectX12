#include "Color.h"

const Color Color::red(255, 0, 0, 255);
const Color Color::green(0, 255, 0, 255);
const Color Color::blue(0, 0, 255, 255);
const Color Color::yellow(255, 255, 0, 255);
const Color Color::white(255, 255, 255, 255);
const Color Color::black(255, 0, 0, 255);

Color::Color() :
	r(255), g(255), b(255), a(255)
{
}

Color::Color(float r, float g, float b, float a) :
	r(r), g(g), b(b), a(a)
{
}