#include "Vec4.h"
#include <math.h>

float Vec4::Magnitude() const { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2)); }

float Vec4::SqrMagnitude() const { return pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2); }

Vec4 Vec4::Normalized() const
{
	return { x / Magnitude(), y / Magnitude(), z / Magnitude(), w / Magnitude() };
}

float Vec4::Distance(const Vec4& v1, const Vec4& v2)
{
	return sqrt(
		pow(v2.x - v1.x, 2) +
		pow(v2.y - v1.y, 2) +
		pow(v2.z - v1.z, 2) +
		pow(v2.w - v1.w, 2));
}

Vec4 Vec4::Max(const Vec4& v1, const Vec4& v2)
{
	return Vec4(
		v1.x >= v2.x ? v1.x : v2.x,
		v1.y >= v2.y ? v1.y : v2.y,
		v1.z >= v2.z ? v1.z : v2.z,
		v1.w >= v2.w ? v1.w : v2.w);
}

Vec4 Vec4::Min(const Vec4& v1, const Vec4& v2)
{
	return Vec4(
		v1.x <= v2.x ? v1.x : v2.x,
		v1.y <= v2.y ? v1.y : v2.z,
		v1.z <= v2.z ? v1.z : v2.z,
		v1.w <= v2.w ? v1.w : v2.w);
}

float Vec4::Dot(const Vec4& v1, const Vec4& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w + v2.w;
}

// もう一方のベクトルとの足し算
Vec4 Vec4::operator+(const Vec4& other) const
{
	return { x + other.x, y + other.y, z + other.z,w + other.w };
}

// もう一方のベクトルとの引き算
Vec4 Vec4::operator-(const Vec4& other) const
{
	return { x - other.x, y - other.y, z - other.z ,w - other.w };
}

// もう一方のベクトルとの掛け算
Vec4 Vec4::operator*(const Vec4& other) const
{
	return { x * other.x, y * other.y, z * other.z ,w * other.w };
}

// もう一方のベクトルとの割り算
Vec4 Vec4::operator/(const Vec4& other) const
{
	return { x / other.x, y / other.y, z / other.z ,w / other.w };
}

// 一つの値との掛け算
Vec4 Vec4::operator*(float num) const
{
	return { x * num, y * num, z * num ,w * num };
}

// 一つの値との割り算
Vec4 Vec4::operator/(float num) const
{
	return { x / num, y / num, z / num ,w / num };
}

// 複合代入演算 +=
Vec4& Vec4::operator+=(const Vec4& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

// 複合代入演算 -=
Vec4& Vec4::operator-=(const Vec4& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}

Vec4& Vec4::operator+=(float num)
{
	x += num;
	y += num;
	z += num;
	w += num;
	return *this;
}

Vec4& Vec4::operator-=(float num)
{
	x -= num;
	y -= num;
	z -= num;
	w -= num;
	return *this;
}

// 複合代入演算 *=
Vec4& Vec4::operator*=(float num)
{
	x *= num;
	y *= num;
	z *= num;
	w *= num;
	return *this;
}

// 複合代入演算 /=
Vec4& Vec4::operator/=(float num)
{
	x += num;
	y += num;
	z += num;
	w += num;
	return *this;
}

Vec4& Vec4::operator=(float num)
{
	x = num;
	y = num;
	z = num;
	w = num;
	return *this;
}

Vec4& Vec4::operator++()
{
	x++;
	y++;
	z++;
	w++;
	return *this;
}

Vec4 Vec4::operator++(int)
{
	Vec4 tmp = *this;
	++* this;
	return tmp;
}

Vec4& Vec4::operator--()
{
	x--;
	y--;
	z--;
	w--;
	return *this;
}

Vec4 Vec4::operator--(int)
{
	Vec4 tmp = *this;
	--* this;
	return tmp;
}

bool Vec4::operator==(const Vec4& other)
{
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool Vec4::operator!=(const Vec4& other)
{
	return x != other.x || y != other.y || z != other.z || w != other.w;
}

bool Vec4::operator>=(const Vec4& other)
{
	return x >= other.x && y >= other.y && z >= other.z && w >= other.w;
}

bool Vec4::operator<=(const Vec4& other)
{
	return x <= other.x && y <= other.y && z <= other.z && w <= other.w;
}

bool Vec4::operator==(float num)
{
	return x == num && y == num && z == num && w == num;
}



bool Vec4::operator!=(float num)
{
	return x != num || y != num || z != num || w != num;
}



bool Vec4::operator>=(float num)
{
	return x >= num && y >= num && z >= num && w >= num;
}



bool Vec4::operator<=(float num)
{
	return x <= num && y <= num && z <= num && w <= num;
}