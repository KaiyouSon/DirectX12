#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class Transform
{
public:
	XMFLOAT3 pos = { 0,0,0 };	// ���W
	XMFLOAT3 scale = { 1,1,1 };	// �X�P�[��
	XMFLOAT3 rot = { 0,0,0 };	// ��]

	// ���[���h�ϊ��s��
	XMMATRIX matWorld;

public:
	Transform();
	Transform(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 rot);
	void Update();
};

