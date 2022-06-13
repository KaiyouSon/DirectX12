#pragma once
#include "Color.h"
#include "MathUtil.h"
#include <d3d12.h>
#include <wrl.h>

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
	// マテリアルの定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffMaterial;
	// トランスフォームの定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform;

	ConstBufferDateMaterial* constMapMaterial;

public:
	ConstBufferDataTransform* constMapTransform = nullptr;
public:
	void MaterialBufferInit();
	void TransformBufferInit();
public:
	Microsoft::WRL::ComPtr<ID3D12Resource> GetConstBuffMaterial();
	Microsoft::WRL::ComPtr<ID3D12Resource> GetConstBuffTransform();

	void SetColor(const Color& color);
};