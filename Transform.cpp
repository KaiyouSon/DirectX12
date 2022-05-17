#include "Transform.h"
#include "MathUtil.h"

Transform::Transform() :
	pos(0, 0, 0), scale(1, 1, 1), rot(0, 0, 0)
{
}

Transform::Transform(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 rot) :
	pos(pos), scale(scale), rot(rot)
{
}

void Transform::Update()
{
	// ワールド変換行列
	//matWorld = XMMatrixIdentity();
	matWorld = Mat4::Identity();

	// スケーリング
	//XMMATRIX matScale;	// スケーリング行列
	//matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	//matWorld *= matScale;	// ワールド変換行列にスケーリングを反映
	Mat4 matScale = Mat4::Scale(Vec3(scale.x, scale.y, scale.z));
	matWorld *= matScale;

	// 回転
	//XMMATRIX matRot; // 回転行列
	//matRot = XMMatrixIdentity();
	//matRot *= XMMatrixRotationX(Radian(rot.x));
	//matRot *= XMMatrixRotationY(Radian(rot.y));
	//matRot *= XMMatrixRotationZ(Radian(rot.z));

	Mat4 matRot = Mat4::Identity();
	matRot *= Mat4::RotateZ(rot.z);
	matRot *= Mat4::RotateX(rot.x);
	matRot *= Mat4::RotateY(rot.y);
	matWorld *= matRot;

	// 平行移動
	//XMMATRIX matTrans;	// 平行移動
	//matTrans = XMMatrixTranslation(pos.x, pos.y, pos.z);	// 平行移動

	Mat4 matTrans = Mat4::Identity();
	matTrans = Mat4::Translate(Vec3(pos.x, pos.y, pos.z));
	matWorld *= matTrans;	// ワールド行列に平行移動を反映
}