#pragma once
#include <d3d12.h>
class GraphicsCommand
{
private:
	HRESULT result;
	// ���\�[�X�o���A
	D3D12_RESOURCE_BARRIER barrierDesc{};
public:
	void PreUpdate();
	void PostUpdate();
};

