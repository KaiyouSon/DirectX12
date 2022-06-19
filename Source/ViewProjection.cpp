#include "Header/ViewProjection.h"
#include "Header/Util.h"
#include "Header/MathUtil.h"
#include "ImGUI/imgui.h"

View* view = View::GetInstance();

void ViewProjection::Initialize()
{
	// ビュー変換行列
	matView = Mat4::ViewConversion(pos, target, up);

	// 並行投影行列の計算
	matProjection2D = Mat4::ParallelConversion(WIN_WIDTH, WIN_HEIGHT);

	// 透視投影行列の計算
	matProjection3D = Mat4::PerspectiveConversion(
		MathUtil::Radian(45),	// 上下画角45度
		(float)WIN_WIDTH / WIN_HEIGHT, // アスペクト比(画面横幅/画面縦幅)
		0.1f, 1000.0f);	// 先端　奥端
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

ViewProjection* ViewProjection::GetInstance()
{
	static ViewProjection* view = new ViewProjection;
	return view;
}

void ViewProjection::DestroyInstance()
{
	delete ViewProjection::GetInstance();
}