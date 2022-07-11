#include "NewEngine/Header/Developer/Object/Other/ViewProjection.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "NewEngine/Header/Developer/Math/MathUtil.h"

View* view = View::GetInstance();

void ViewProjection::Initialize()
{
	// ビュー変換行列
	matView = MathUtil::ConvertViewProjectionMat(pos, target, up);

	// 並行投影行列の計算
	matProjection2D = MathUtil::ConvertOrthoGrphicProjectionMat(WIN_WIDTH, WIN_HEIGHT);

	nearZ = 0.1f, farZ = 1000.0f;

	// 透視投影行列の計算
	matProjection3D = MathUtil::ConvertPerspectiveProjectionMat(
		MathUtil::Radian(45),	// 上下画角45度
		(float)WIN_WIDTH / WIN_HEIGHT, // アスペクト比(画面横幅/画面縦幅)
		nearZ, farZ);	// 先端　奥端
}

void ViewProjection::SetPos(const Vec3& pos)
{
	this->pos = pos;
	matView = MathUtil::ConvertViewProjectionMat(pos, target, up);
}
void ViewProjection::SetTarget(const Vec3& target)
{
	this->target = target;
	matView = MathUtil::ConvertViewProjectionMat(pos, target, up);
}
void ViewProjection::SetUp(const Vec3& up)
{
	this->up = up;
	matView = MathUtil::ConvertViewProjectionMat(pos, target, up);
}

Vec3 ViewProjection::GetPos()
{
	return pos;
}
Vec3 ViewProjection::GetTarget()
{
	return target;
}
Vec3 ViewProjection::GetUp()
{
	return up;
}

float ViewProjection::GetNearZ()
{
	return nearZ;
}

float ViewProjection::GetFarZ()
{
	return farZ;
}

ViewProjection* ViewProjection::GetInstance()
{
	static ViewProjection* view = new ViewProjection;
	return view;
}
void ViewProjection::DestroyInstance()
{
	delete GetInstance();
}