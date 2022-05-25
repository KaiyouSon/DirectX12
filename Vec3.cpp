#include "Vec3.h"
#include <math.h>

const Vec3 Vec3::left(-1, 0, 0);
const Vec3 Vec3::right(1, 0, 0);
const Vec3 Vec3::up(0, 1, 0);
const Vec3 Vec3::down(0, -1, 0);
const Vec3 Vec3::forward(0, 0, 1);
const Vec3 Vec3::back(0, 0, -1);
const Vec3 Vec3::one(1, 1, 1);
const Vec3 Vec3::zero(0, 0, 0);

float Vec3::Magnitude() const { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); }

float Vec3::SqrMagnitude() const { return pow(x, 2) + pow(y, 2) + pow(z, 2); }

Vec3 Vec3::Normalized() const { return { x / Magnitude(), y / Magnitude(), z / Magnitude() }; }

float Vec3::Dot(const Vec3& v1, const Vec3& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

Vec3 Vec3::Cross(const Vec3& v1, const Vec3& v2)
{
	return {
		(v1.y * v2.z - v1.z * v2.y),
		(v1.z * v2.x - v1.x * v2.z),
		(v1.x * v2.y - v1.y * v2.x) };
}

float Vec3::Distance(const Vec3& v1, const Vec3& v2)
{
	return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2) + pow(v2.z - v1.z, 2));
}

Vec3 Vec3::Max(const Vec3& v1, const Vec3& v2)
{
	return Vec3(v1.x >= v2.x ? v1.x : v2.x, v1.y >= v2.y ? v1.y : v2.y, v1.z >= v2.z ? v1.z : v2.z);
}

Vec3 Vec3::Min(const Vec3& v1, const Vec3& v2)
{
	return Vec3(v1.x <= v2.x ? v1.x : v2.x, v1.y <= v2.y ? v1.y : v2.z, v1.z <= v2.z ? v1.z : v2.z);
}

// もう一方のベクトルとの足し算
Vec3 Vec3::operator+(const Vec3& other) const { return { x + other.x, y + other.y, z + other.z }; }

// もう一方のベクトルとの引き算
Vec3 Vec3::operator-(const Vec3& other) const { return { x - other.x, y - other.y, z - other.z }; }

// もう一方のベクトルとの掛け算
Vec3 Vec3::operator*(const Vec3& other) const { return { x * other.x, y * other.y, z * other.z }; }

// もう一方のベクトルとの割り算
Vec3 Vec3::operator/(const Vec3& other) const { return { x / other.x, y / other.y, z / other.z }; }

// 一つの値との掛け算
Vec3 Vec3::operator*(float num) const { return { x * num, y * num, z * num }; }

// 一つの値との割り算
Vec3 Vec3::operator/(float num) const { return { x / num, y / num, z / num }; }

// 複合代入演算 +=
Vec3& Vec3::operator+=(const Vec3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

// 複合代入演算 -=
Vec3& Vec3::operator-=(const Vec3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vec3& Vec3::operator+=(float num)
{
	x += num;
	y += num;
	z += num;
	return *this;
}

Vec3& Vec3::operator-=(float num)
{
	x -= num;
	y -= num;
	z -= num;
	return *this;
}

// 複合代入演算 *=
Vec3& Vec3::operator*=(float num)
{
	x *= num;
	y *= num;
	z *= num;
	return *this;
}

// 複合代入演算 /=
Vec3& Vec3::operator/=(float num)
{
	x += num;
	y += num;
	z += num;
	return *this;
}

Vec3& Vec3::operator=(float num)
{
	x = num;
	y = num;
	z = num;
	return *this;
}

Vec3& Vec3::operator++()
{
	x++;
	y++;
	z++;
	return *this;
}

Vec3 Vec3::operator++(int)
{
	Vec3 tmp = *this;
	++* this;
	return tmp;
}

Vec3& Vec3::operator--()
{
	x--;
	y--;
	z--;
	return *this;
}

Vec3 Vec3::operator--(int)
{
	Vec3 tmp = *this;
	--* this;
	return tmp;
}

bool Vec3::operator==(const Vec3& other) { return x == other.x && y == other.y && z == other.z; }

bool Vec3::operator!=(const Vec3& other) { return x != other.x || y != other.y || z != other.z; }

bool Vec3::operator>=(const Vec3& other) { return x >= other.x && y >= other.y && z >= other.z; }

bool Vec3::operator<=(const Vec3& other) { return x <= other.x && y <= other.y && z <= other.z; }

bool Vec3::operator==(float num) { return x == num && y == num && z == num; }

bool Vec3::operator!=(float num) { return x != num || y != num || z != num; }

bool Vec3::operator>=(float num) { return x >= num && y >= num && z >= num; }

bool Vec3::operator<=(float num) { return x <= num && y <= num && z <= num; }