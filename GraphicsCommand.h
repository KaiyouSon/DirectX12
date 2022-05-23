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
	void PreDraw();
	void Draw3D();
	void Draw2D();
	void PostDraw();
	void SetBackgroundColor(float Red, float Green, float Blue);

	static GraphicsCommand& GetInstance();
private:
	GraphicsCommand() = default;
	~GraphicsCommand() = default;

	GraphicsCommand(const GraphicsCommand&) = delete;
	GraphicsCommand& operator=(const GraphicsCommand&) = delete;
	GraphicsCommand(const GraphicsCommand&&) = delete;
	GraphicsCommand& operator=(const GraphicsCommand&&) = delete;
};

