#pragma once

#include <DirectXMath.h>
using namespace DirectX;

class ViewProjection
{
public:
	// �r���[�ϊ��s��
	XMMATRIX matView;

	// �������e�s��̌v�Z
	XMMATRIX matProjection;

public:
	void Initialize();
};