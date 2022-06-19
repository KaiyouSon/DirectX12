#pragma once
#include <d3d12.h>
#include <wrl.h>

class RootSignature
{
private:
	// ルートシグネチャ
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
public:
	// 初期化
	void Initialize();
	// ルートシグネチャを取得する関数
	Microsoft::WRL::ComPtr<ID3D12RootSignature> GetRootSignature();

	static RootSignature* GetInstance();
	static void DestroyInstance();
private:
	RootSignature() = default;
	~RootSignature() = default;

	RootSignature(const RootSignature&) = delete;
	RootSignature& operator=(const RootSignature&) = delete;
	RootSignature(const RootSignature&&) = delete;
	RootSignature& operator=(const RootSignature&&) = delete;
};

