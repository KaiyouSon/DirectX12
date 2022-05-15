#pragma once
#include <d3d12.h>
class GraphicsCommand
{
private:
	HRESULT result;
	// リソースバリア
	D3D12_RESOURCE_BARRIER barrierDesc{};
	// レンダーターゲットビューのハンドル
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
	// 画面色
	float clearColor[4];

public:
	~GraphicsCommand();
	void PreUpdate();
	void PostUpdate();
	void SetBackgroundColor(float Red, float Green, float Blue);
};

