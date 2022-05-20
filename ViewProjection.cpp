#include "ViewProjection.h"
#include "Util.h"
#include "MathUtil.h"
#include "Input.h"

static float distance = 0;
Vec3 vec;
static float angle = 270;

void ViewProjection::Initialize()
{
	// �r���[�ϊ��s��
	matView = Mat4::ViewConversion(pos, target, up);

	// ���s���e�s��̌v�Z
	matProjection2D = Mat4::ParallelConversion(WIN_WIDTH, WIN_HEIGHT);

	// �������e�s��̌v�Z
	matProjection3D = Mat4::PerspectiveConversion(
		Radian(45),	// �㉺��p45�x
		(float)WIN_WIDTH / WIN_HEIGHT, // �A�X�y�N�g��(��ʉ���/��ʏc��)
		0.1f, 1000.0f);	// ��[�@���[

	vec = pos - target;
	distance = Vec3::Distance(pos, target);
}

void ViewProjection::SetPos(const Vec3& pos)
{
	this->pos = pos;
	matView = Mat4::ViewConversion(pos, target, up);
}

void ViewProjection::SetTarget(const Vec3& target)
{
	this->target = target;
	matView = Mat4::ViewConversion(pos, target, up);
}

void ViewProjection::SetUp(const Vec3& up)
{
	this->up = up;
	matView = Mat4::ViewConversion(pos, target, up);
}

ViewProjection& ViewProjection::GetInstance()
{
	static ViewProjection view;
	return view;
}
