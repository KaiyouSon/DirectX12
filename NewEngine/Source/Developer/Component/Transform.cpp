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
	matScale = MathUtil::ConvertScalingMat(scale);		 // スケーリング
	matRot = Mat4::Identity();
	matRot *= MathUtil::ConvertRotationZAxisMat(rot.z); // z軸回転
	matRot *= MathUtil::ConvertRotationXAxisMat(rot.x); // x軸回転
	matRot *= MathUtil::ConvertRotationYAxisMat(rot.y); // y軸回転
	matTrans = MathUtil::ConvertTranslationMat(pos);	 // 平行移動

	matWorld = Mat4::Identity();
	matWorld *= matScale;
	matWorld *= matRot;
	matWorld *= matTrans;	// ワールド行列に平行移動を反映
}