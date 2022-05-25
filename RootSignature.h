#pragma once
#include <d3d12.h>
#include <wrl.h>

class RootSignature
{
private:
	// ���[�g�V�O�l�`��
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
public:
	// ������
	void Initialize();
	// ���[�g�V�O�l�`�����擾����֐�
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

