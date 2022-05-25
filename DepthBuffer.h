#pragma once
#include <d3d12.h>
#include <wrl.h>

class DepthBuffer
{
private:
	// 深度ビュー用でスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
public:
	void Initialize();

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetDsvHeap();

	static DepthBuffer* GetInstance();
	static void DestroyInstance();
private:
	DepthBuffer() = default;
	~DepthBuffer() = default;

	DepthBuffer(const DepthBuffer&) = delete;
	DepthBuffer& operator=(const DepthBuffer&) = delete;
	DepthBuffer(const DepthBuffer&&) = delete;
	DepthBuffer& operator=(const DepthBuffer&&) = delete;
};