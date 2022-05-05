#include "Transform.h"

Transform::Transform()
{

}

Transform::Transform(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 rot)
{
}

void Transform::Update()
{
	//// 単位行列を代入
	//constMapTransform->mat = XMMatrixIdentity();

	//constMapTransform->mat.r[0].m128_f32[0] = 2.0f / newEngineWin->GetWinWidth();
	//constMapTransform->mat.r[1].m128_f32[1] = -2.0f / newEngineWin->GetWinHeight();

	//constMapTransform->mat.r[3].m128_f32[0] = -1.0f;
	//constMapTransform->mat.r[3].m128_f32[1] = 1.0f;

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