#pragma once
#include <d3d12.h>
class ShaderCompiler
{
private:
	ID3DBlob* vsBlob = nullptr;		// 頂点シェーダオブジェクト
	ID3DBlob* psBlob = nullptr;		// ピクセルシェーダオブジェクト
	ID3DBlob* psBlob2 = nullptr;		// ピクセルシェーダオブジェクト
	ID3DBlob* errorBlob = nullptr;	// エラーオブジェクト
	D3D12_INPUT_ELEMENT_DESC inputLayout[3];	// 頂点レイアウト

public:
	// 頂点シェーダファイルの読み込みとコンパイル
	void BasicVSCompile();
	// ピクセルシェーダファイルの読み込みとコンパイル
	void BasicPSCompile();
public:
	ID3DBlob* GetvsBlob();		 // 頂点シェーダオブジェクトを取得する関数
	ID3DBlob* GetpsBlob();		 // ピクセルシェーダオブジェクトを取得する関数
	ID3DBlob* GetpsBlob2();		 // ピクセルシェーダオブジェクトを取得する関数
	ID3DBlob** GeterrorBlobAddress();	 // エラーオブジェクトを取得する関数
	D3D12_INPUT_ELEMENT_DESC* GetInputLayout();		// 頂点レイアウトを取得する関数
	int GetInputLayoutSize();						// 頂点レイアウトの要素数を取得する関数

	static ShaderCompiler& GetInstance();

private:
	ShaderCompiler() = default;
	~ShaderCompiler() = default;

	ShaderCompiler(const ShaderCompiler&) = delete;
	ShaderCompiler& operator=(const ShaderCompiler&) = delete;
	ShaderCompiler(const ShaderCompiler&&) = delete;
	ShaderCompiler& operator=(const ShaderCompiler&&) = delete;
};