#include "NewEngine/Header/Developer/Math/Quaternion.h"
#include <math.h>

Quaternion::Quaternion() :
	x(0), y(0), z(0), w(0)
{
}

Quaternion::Quaternion(float x, float y, float z, float w) :
	x(x), y(y), z(z), w(w)
{
}

Quaternion Quaternion::AngleAxis(const float& angle, const Vec3& axis)
{
	return
	{
		axis.Normalized().x * sinf(angle / 2),
		axis.Normalized().y * sinf(angle / 2),
		axis.Normalized().z * sinf(angle / 2),
		cosf(angle / 2),
	};
}
