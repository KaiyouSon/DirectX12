#pragma once
#include <d3d12.h>
#include <wrl.h>
class ShaderCompiler
{
private:
	Microsoft::WRL::ComPtr <ID3DBlob> vsBlob;		// 頂点シェーダオブジェクト
	Microsoft::WRL::ComPtr <ID3DBlob> psBlob;		// ピクセルシェーダオブジェクト
	Microsoft::WRL::ComPtr <ID3DBlob> psBlob2;		// ピクセルシェーダオブジェクト
	Microsoft::WRL::ComPtr <ID3DBlob> errorBlob;	// エラーオブジェクト
	D3D12_INPUT_ELEMENT_DESC inputLayout[3];	// 頂点レイアウト

public:
	// 頂点シェーダファイルの読み込みとコンパイル
	void BasicVSCompile();
	// ピクセルシェーダファイルの読み込みとコンパイル
	void BasicPSCompile();
	void BasicPSCompile2();
public:
	Microsoft::WRL::ComPtr<ID3DBlob> GetvsBlob();		 // 頂点シェーダオブジェクトを取得する関数
	Microsoft::WRL::ComPtr<ID3DBlob> GetpsBlob();		 // ピクセルシェーダオブジェクトを取得する関数
	Microsoft::WRL::ComPtr<ID3DBlob> GetpsBlob2();		 // ピクセルシェーダオブジェクトを取得する関数
	Microsoft::WRL::ComPtr<ID3DBlob> GeterrorBlob();					 // エラーオブジェクトを取得する関数
	D3D12_INPUT_ELEMENT_DESC* GetInputLayout();		// 頂点レイアウトを取得する関数
	int GetInputLayoutSize();						// 頂点レイアウトの要素数を取得する関数

	static ShaderCompiler* GetInstance();
	static void DestroyInstance();
private:
	ShaderCompiler() = default;
	~ShaderCompiler() = default;

	ShaderCompiler(const ShaderCompiler&) = delete;
	ShaderCompiler& operator=(const ShaderCompiler&) = delete;
	ShaderCompiler(const ShaderCompiler&&) = delete;
	ShaderCompiler& operator=(const ShaderCompiler&&) = delete;
};