#pragma once
#include <d3d12.h>

class DepthBuffer
{
private:
	// 深度ビュー用でスクリプタヒープ
	ID3D12DescriptorHeap* dsvHeap = nullptr;
public:
	void Initialize();

	ID3D12DescriptorHeap* GetDsvHeap();

	static DepthBuffer& GetInstance();
private:
	DepthBuffer() = default;
	~DepthBuffer() = default;

	DepthBuffer(const DepthBuffer&) = delete;
	DepthBuffer& operator=(const DepthBuffer&) = delete;
	DepthBuffer(const DepthBuffer&&) = delete;
	DepthBuffer& operator=(const DepthBuffer&&) = delete;
};