#include "Transform.h"

Transform::Transform() :
	pos(0, 0, 0), scale(1, 1, 1), rot(0, 0, 0)
{
}

//Transform::Transform(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 rot) :
//	pos(pos), scale(scale), rot(rot)
//{
//}

Transform::Transform(Vec3 pos, Vec3 scale, Vec3 rot) :
	pos(pos), scale(scale), rot(rot)
{
}

void Transform::Update()
{
	// スケーリング
	matScale = Mat4::Scale(scale);
	matWorld = matWorld * matScale;

	// 回転
	matRot = matRot * Mat4::RotateZ(rot.z);
	matRot = matRot * Mat4::RotateX(rot.x);
	matRot = matRot * Mat4::RotateY(rot.y);
	matWorld = matWorld * matRot;

	// 平行移動
	matTrans = Mat4::Translate(pos);
	matWorld = matWorld * matTrans;	// ワールド行列に平行移動を反映
}