#pragma once
#include "Mat4.h"
#include "Vec4.h"
#include <d3d12.h>

// 定数バッファ用データ構造体(マテリアル)
struct ConstBufferDateMaterial
{
	Vec4 color;	// 色(RGBA)
};

// 定数バッファ用データ構造体(3D変換行列)
struct ConstBufferDataTransform
{
	Mat4 mat;	//3D変換行列
};

class ConstantBuffer
{
private:
	ID3D12Resource* constBuffMaterial;	// マテリアルの定数バッファ
	ID3D12Resource* constBuffTransform;	// トランスフォームの定数バッファ

public:
	ConstBufferDataTransform* constMapTransform = nullptr;
public:
	void MaterialBufferInit();
	void TransformBufferInit();
public:
	ID3D12Resource* GetConstBuffMaterial();
	ID3D12Resource* GetConstBuffTransform();

	void SetColor(Vec4 color);
};