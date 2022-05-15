#pragma once
#include <d3d12.h>
class GraphicsCommand
{
private:
	HRESULT result;
	// ���\�[�X�o���A
	D3D12_RESOURCE_BARRIER barrierDesc{};
	// �����_�[�^�[�Q�b�g�r���[�̃n���h��
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
	// ��ʐF
	float clearColor[4];

public:
	~GraphicsCommand();
	void PreUpdate();
	void PostUpdate();
	void SetBackgroundColor(float Red, float Green, float Blue);
};

