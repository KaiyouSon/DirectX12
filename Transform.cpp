#include "Transform.h"

Transform::Transform()
{

}

Transform::Transform(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 rot)
{
}

void Transform::Update()
{
	// ワールド変換行列
	matWorld = XMMatrixIdentity();

	// スケーリング
	XMMATRIX matScale;	// スケーリング行列
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matWorld *= matScale;	// ワールド変換行列にスケーリングを反映

	// 回転
	XMMATRIX matRot; // 回転行列
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationX(rot.x);
	matRot *= XMMatrixRotationY(rot.y);
	matRot *= XMMatrixRotationZ(rot.z);
	matWorld *= matRot;

	// 平行移動
	XMMATRIX matTrans;	// 平行移動
	matTrans = XMMatrixTranslation(pos.x, pos.y, pos.z);	// 平行移動
	matWorld *= matTrans;	// ワールド行列に平行移動を反映
}