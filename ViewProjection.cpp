#include "ViewProjection.h"
#include "Util.h"
#include "MathUtil.h"
#include "Input.h"
#include "MathUtil.h"
#include "Vec3.h"

void ViewProjection::Initialize()
{
	// ビュー変換行列
	//matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

	Vec3 tmpEye = { eye.x,eye.y,eye.z };
	Vec3 tmpTarget = { target.x,target.y,target.z };
	Vec3 tmpUp = { up.x,up.y,up.z };
	matView = Mat4::ViewConversion(tmpEye, tmpTarget, tmpUp);

	// 並行投影行列の計算
	matProjection2D = XMMatrixOrthographicOffCenterLH(
		0, WIN_WIDTH,
		WIN_HEIGHT, 0,
		0, 1);

	// 透視投影行列の計算
	//matProjection3D = XMMatrixPerspectiveFovLH(
	//	XMConvertToRadians(45),	// 上下画角45度
	//	(float)WIN_WIDTH / WIN_HEIGHT, // アスペクト比(画面横幅/画面縦幅)
	//	0.1f, 1000.0f);	// 先端　奥端

	matProjection3D = Mat4::PerspectiveConversion(
		Radian(45),
		WIN_WIDTH / WIN_HEIGHT,
		0.1f, 1000.0f);
}

static float distance = 0;
Vec3 vec;

void ViewProjection::Update()
{
	// カメラの視点移動
	if (!Input::GetInstance().GetKey(DIK_LSHIFT))
	{
		if (Input::GetInstance().GetMouseWheel())
		{
			target.x += Input::GetInstance().GetMouseVelocity().x * 0.05;
			target.y -= Input::GetInstance().GetMouseVelocity().y * 0.05;
			SetTarget(this->target);
		}
	}

	// カメラの平行移動
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
