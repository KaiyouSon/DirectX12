#pragma once
#include "ConstantBuffer.h"

#include <DirectXMath.h>
using namespace DirectX;

class Sprite
{

private:
	int vbArraySize;	// ���_�f�[�^�̗v�f��
	int ibArraySize;	// �C���f�b�N�X�f�[�^�̗v�f��
public:
	Sprite();
	void Initialize();
	void DrawBox(XMFLOAT4 color);
	void DrawGraph();
};