#include "ViewProjection.h"
#include "Util.h"
#include "MathUtil.h"
#include "Input.h"
#include "MathUtil.h"
#include "Vec3.h"

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
}

static float distance = 0;
Vec3 vec;

void ViewProjection::Update()
{
	//	// �J�����̎��_�ړ�
	//	if (!Input::GetInstance().GetKey(DIK_LSHIFT))
	//	{
	//		if (Input::GetInstance().GetMouseWheel())
	//		{
	//			target.x += Input::GetInstance().GetMouseVelocity().x * 0.05;
	//			target.y -= Input::GetInstance().GetMouseVelocity().y * 0.05;
	//			SetTarget(this->target);
	//		}
	//	}
	//
	//	// �J�����̕��s�ړ�
	//	if (Input::GetInstance().GetKey(DIK_LSHIFT))
	//	{
	//		if (Input::GetInstance().GetMouseWheel())
	//		{
	//			eye.x -= Input::GetInstance().GetMouseVelocity().x * 0.05;
	//			eye.y += Input::GetInstance().GetMouseVelocity().y * 0.05;
	//			SetEye(this->eye);
	//			target.x -= Input::GetInstance().GetMouseVelocity().x * 0.05;
	//			target.y += Input::GetInstance().GetMouseVelocity().y * 0.05;
	//			SetTarget(this->target);
	//		}
	//	}
	//
	//	Vec3 tmpEye = { eye.x,eye.y,eye.z };
	//	Vec3 tmpTarget = { target.x,target.y,target.z };
	//
	//	vec = tmpEye - tmpTarget;
	//	distance = Vec3::Distance(tmpEye, tmpTarget);
	//
	//	if (Input::GetInstance().GetMouseVelocity().z < 0)
	//	{
	//		distance += 2;
	//		eye.x = vec.Normalized().x * distance;
	//		eye.y = vec.Normalized().y * distance;
	//		eye.z = vec.Normalized().z * distance;
	//		SetEye(this->eye);
	//	}
	//
	//	if (Input::GetInstance().GetMouseVelocity().z > 0)
	//	{
	//		distance -= 2;
	//		eye.x = vec.Normalized().x * distance;
	//		eye.y = vec.Normalized().y * distance;
	//		eye.z = vec.Normalized().z * distance;
	//		SetEye(this->eye);
	//	}
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
