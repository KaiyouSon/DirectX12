#include "ViewProjection.h"
#include "Util.h"
#include "MathUtil.h"
#include "Input.h"
#include "MathUtil.h"
#include "Vec3.h"

void ViewProjection::Initialize()
{
	// �r���[�ϊ��s��
	//matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

	Vec3 tmpEye = { eye.x,eye.y,eye.z };
	Vec3 tmpTarget = { target.x,target.y,target.z };
	Vec3 tmpUp = { up.x,up.y,up.z };
	matView = Mat4::ViewConversion(tmpEye, tmpTarget, tmpUp);

	// ���s���e�s��̌v�Z
	matProjection2D = XMMatrixOrthographicOffCenterLH(
		0, WIN_WIDTH,
		WIN_HEIGHT, 0,
		0, 1);

	// �������e�s��̌v�Z
	//matProjection3D = XMMatrixPerspectiveFovLH(
	//	XMConvertToRadians(45),	// �㉺��p45�x
	//	(float)WIN_WIDTH / WIN_HEIGHT, // �A�X�y�N�g��(��ʉ���/��ʏc��)
	//	0.1f, 1000.0f);	// ��[�@���[

	matProjection3D = Mat4::PerspectiveConversion(
		Radian(45),
		WIN_WIDTH / WIN_HEIGHT,
		0.1f, 1000.0f);
}

static float distance = 0;
Vec3 vec;

void ViewProjection::Update()
{
	// �J�����̎��_�ړ�
	if (!Input::GetInstance().GetKey(DIK_LSHIFT))
	{
		if (Input::GetInstance().GetMouseWheel())
		{
			target.x += Input::GetInstance().GetMouseVelocity().x * 0.05;
			target.y -= Input::GetInstance().GetMouseVelocity().y * 0.05;
			SetTarget(this->target);
		}
	}

	// �J�����̕��s�ړ�
	if (Input::GetInstance().GetKey(DIK_LSHIFT))
	{
		if (Input::GetInstance().GetMouseWheel())
		{
			eye.x -= Input::GetInstance().GetMouseVelocity().x * 0.05;
			eye.y += Input::GetInstance().GetMouseVelocity().y * 0.05;
			SetEye(this->eye);
			target.x -= Input::GetInstance().GetMouseVelocity().x * 0.05;
			target.y += Input::GetInstance().GetMouseVelocity().y * 0.05;
			SetTarget(this->target);
		}
	}

	Vec3 tmpEye = { eye.x,eye.y,eye.z };
	Vec3 tmpTarget = { target.x,target.y,target.z };

	vec = tmpEye - tmpTarget;
	distance = Vec3::Distance(tmpEye, tmpTarget);

	if (Input::GetInstance().GetMouseVelocity().z < 0)
	{
		distance += 2;
		eye.x = vec.Normalized().x * distance;
		eye.y = vec.Normalized().y * distance;
		eye.z = vec.Normalized().z * distance;
		SetEye(this->eye);
	}

	if (Input::GetInstance().GetMouseVelocity().z > 0)
	{
		distance -= 2;
		eye.x = vec.Normalized().x * distance;
		eye.y = vec.Normalized().y * distance;
		eye.z = vec.Normalized().z * distance;
		SetEye(this->eye);
	}
}

void ViewProjection::SetEye(const XMFLOAT3& eye)
{
	//this->eye = eye;
	//matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

	Vec3 tmpEye = { eye.x,eye.y,eye.z };
	Vec3 tmpTarget = { target.x,target.y,target.z };
	Vec3 tmpUp = { up.x,up.y,up.z };
	matView = Mat4::ViewConversion(tmpEye, tmpTarget, tmpUp);
}

void ViewProjection::SetTarget(const XMFLOAT3& target)
{
	//this->target = target;
	//matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

	Vec3 tmpEye = { eye.x,eye.y,eye.z };
	Vec3 tmpTarget = { target.x,target.y,target.z };
	Vec3 tmpUp = { up.x,up.y,up.z };
	matView = Mat4::ViewConversion(tmpEye, tmpTarget, tmpUp);
}

void ViewProjection::SetUp(const XMFLOAT3& up)
{
	//this->up = up;
	//matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

	Vec3 tmpEye = { eye.x,eye.y,eye.z };
	Vec3 tmpTarget = { target.x,target.y,target.z };
	Vec3 tmpUp = { up.x,up.y,up.z };
	matView = Mat4::ViewConversion(tmpEye, tmpTarget, tmpUp);
}

ViewProjection& ViewProjection::GetInstance()
{
	static ViewProjection view;
	return view;
}
