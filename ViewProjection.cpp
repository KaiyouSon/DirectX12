#include "ViewProjection.h"
#include "Util.h"
#include "MathUtil.h"
#include "Input.h"
#include "MathUtil.h"
#include "Vec3.h"

void ViewProjection::Initialize()
{
	// ビュー変換行列
	matView = Mat4::ViewConversion(pos, target, up);

	// 並行投影行列の計算
	matProjection2D = Mat4::ParallelConversion(WIN_WIDTH, WIN_HEIGHT);

	// 透視投影行列の計算
	matProjection3D = Mat4::PerspectiveConversion(
		Radian(45),	// 上下画角45度
		(float)WIN_WIDTH / WIN_HEIGHT, // アスペクト比(画面横幅/画面縦幅)
		0.1f, 1000.0f);	// 先端　奥端
}

static float distance = 0;
Vec3 vec;

void ViewProjection::Update()
{
	//	// カメラの視点移動
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
	//	// カメラの平行移動
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
