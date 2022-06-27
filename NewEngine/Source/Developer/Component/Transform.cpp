#include "NewEngine/Header/Developer/Component/Transform.h"

Transform::Transform() :
	pos(0, 0, 0), scale(1, 1, 1), rot(0, 0, 0)
{
	componentName = "Transform";
}

Transform::Transform(Vec3 pos, Vec3 scale, Vec3 rot) :
	pos(pos), scale(scale), rot(rot)
{
	componentName = "Transform";
}

void Transform::Update()
{
	matScale = Mat4::Scale(scale);		// スケーリング
	matRot = Mat4::Identity();
	matRot *= Mat4::RotateZ(rot.z);		// z軸回転
	matRot *= Mat4::RotateX(rot.x);		// x軸回転
	matRot *= Mat4::RotateY(rot.y);		// y軸回転
	matTrans = Mat4::Translate(pos);	// 平行移動
	
	matWorld = Mat4::Identity();
	matWorld *= matScale;
	matWorld *= matRot;
	matWorld *= matTrans;	// ワールド行列に平行移動を反映
}