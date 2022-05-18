#include "ShaderCompiler.h"

#include <string>
#include <cassert>

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

void ShaderCompiler::BasicVSCompile()
{
	HRESULT result;

	//--------------- 頂点シェーダファイルの読み込みとコンパイル ---------------//
	// 頂点シェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"BasicVS.hlsl", // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "vs_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&vsBlob, &errorBlob);

	//----------------------- シェーダのエラー内容を表示 -----------------------//
	// エラーなら
	if (FAILED(result))
	{
		// errorBlobからエラー内容をstring型にコピー
		std::string error;
		error.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(error.c_str());
		assert(0);
	}

	//--------------- 頂点シェーダに渡すための頂点データを整える ---------------//
	// 頂点レイアウト
	inputLayout[0] =
	{	// xyz座標
		"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
		D3D12_APPEND_ALIGNED_ELEMENT,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	};
	inputLayout[1] =
	{	// xyz座標
		"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
		D3D12_APPEND_ALIGNED_ELEMENT,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	};
	inputLayout[2] =
	{	// uv座標
		"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
		D3D12_APPEND_ALIGNED_ELEMENT,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0

	};
}

void ShaderCompiler::BasicPSCompile()
{
	HRESULT result;

	//------------- ピクセルシェーダファイルの読み込みとコンパイル -------------//
	// ピクセルシェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"BasicPS.hlsl", // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "ps_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&psBlob, &errorBlob);

	//----------------------- シェーダのエラー内容を表示 -----------------------//
	// エラーなら
	if (FAILED(result))
	{
		// errorBlobからエラー内容をstring型にコピー
		std::string error;
		error.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(error.c_str());
		assert(0);
	}

	//------------- ピクセルシェーダファイルの読み込みとコンパイル -------------//
	// ピクセルシェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"BasicPS2.hlsl", // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "ps_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&psBlob2, &errorBlob);

	//----------------------- シェーダのエラー内容を表示 -----------------------//
	// エラーなら
	if (FAILED(result))
	{
		// errorBlobからエラー内容をstring型にコピー
		std::string error;
		error.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(error.c_str());
		assert(0);
	}
}

ID3DBlob* ShaderCompiler::GetvsBlob()
{
	return vsBlob;
}

ID3DBlob* ShaderCompiler::GetpsBlob()
{
	return psBlob;
}

ID3DBlob* ShaderCompiler::GetpsBlob2()
{
	return psBlob2;
}

ID3DBlob** ShaderCompiler::GeterrorBlobAddress()
{
	return &errorBlob;
}

D3D12_INPUT_ELEMENT_DESC* ShaderCompiler::GetInputLayout()
{
	return inputLayout;
}

int ShaderCompiler::GetInputLayoutSize()
{
	return sizeof(inputLayout) / sizeof(inputLayout[0]);
}

ShaderCompiler& ShaderCompiler::GetInstance()
{
	static ShaderCompiler sharderCompiler;
	return sharderCompiler;
}