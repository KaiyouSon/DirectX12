#include "NewEngine/Header/Developer/Object/Other/ViewProjection.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "NewEngine/Header/Developer/Math/MathUtil.h"

View* view = View::GetInstance();

void ViewProjection::Initialize()
{
	// �r���[�ϊ��s��
	matView = MathUtil::ConvertViewProjectionMat(pos, target, up);

	// ���s���e�s��̌v�Z
	matProjection2D = MathUtil::ConvertOrthoGrphicProjectionMat(WIN_WIDTH, WIN_HEIGHT);

	nearZ = 0.1f, farZ = 1000.0f;

	// �������e�s��̌v�Z
	matProjection3D = MathUtil::ConvertPerspectiveProjectionMat(
		MathUtil::Radian(45),	// �㉺��p45�x
		(float)WIN_WIDTH / WIN_HEIGHT, // �A�X�y�N�g��(��ʉ���/��ʏc��)
		nearZ, farZ);	// ��[�@���[
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