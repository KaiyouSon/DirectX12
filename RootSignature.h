#pragma once
#include <d3d12.h>

class RootSignature
{
private:
	// ���[�g�V�O�l�`��
	ID3D12RootSignature* rootSignature;
public:
	void Initialize();

	ID3D12RootSignature* GetRootSignature(); // ���[�g�V�O�l�`�����擾����֐�

	static RootSignature& GetInstance();
private:
	RootSignature() = default;
	~RootSignature() = default;

	RootSignature(const RootSignature&) = delete;
	RootSignature& operator=(const RootSignature&) = delete;
	RootSignature(const RootSignature&&) = delete;
	RootSignature& operator=(const RootSignature&&) = delete;
};

