#include "Header/ViewProjection.h"
#include "Header/Util.h"
#include "Header/MathUtil.h"
#include "ImGUI/imgui.h"

View* view = View::GetInstance();

void ViewProjection::Initialize()
{
	// �r���[�ϊ��s��
	matView = Mat4::ViewConversion(pos, target, up);

	// ���s���e�s��̌v�Z
	matProjection2D = Mat4::ParallelConversion(WIN_WIDTH, WIN_HEIGHT);

	// �������e�s��̌v�Z
	matProjection3D = Mat4::PerspectiveConversion(
		MathUtil::Radian(45),	// �㉺��p45�x
		(float)WIN_WIDTH / WIN_HEIGHT, // �A�X�y�N�g��(��ʉ���/��ʏc��)
		0.1f, 1000.0f);	// ��[�@���[
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