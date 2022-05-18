#pragma once
#include <d3d12.h>

class RootSignature
{
private:
	// ルートシグネチャ
	ID3D12RootSignature* rootSignature;
public:
	void Initialize();

	ID3D12RootSignature* GetRootSignature(); // ルートシグネチャを取得する関数

	static RootSignature& GetInstance();
private:
	RootSignature() = default;
	~RootSignature() = default;

	RootSignature(const RootSignature&) = delete;
	RootSignature& operator=(const RootSignature&) = delete;
	RootSignature(const RootSignature&&) = delete;
	RootSignature& operator=(const RootSignature&&) = delete;
};

