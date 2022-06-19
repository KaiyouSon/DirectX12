#pragma once
#include <d3d12.h>
#include <wrl.h>
class ShaderCompiler
{
private:
	Microsoft::WRL::ComPtr <ID3DBlob> vsBlob;		// ���_�V�F�[�_�I�u�W�F�N�g
	Microsoft::WRL::ComPtr <ID3DBlob> psBlob;		// �s�N�Z���V�F�[�_�I�u�W�F�N�g
	Microsoft::WRL::ComPtr <ID3DBlob> psBlob2;		// �s�N�Z���V�F�[�_�I�u�W�F�N�g
	Microsoft::WRL::ComPtr <ID3DBlob> errorBlob;	// �G���[�I�u�W�F�N�g
	D3D12_INPUT_ELEMENT_DESC inputLayout[3];	// ���_���C�A�E�g

public:
	// ���_�V�F�[�_�t�@�C���̓ǂݍ��݂ƃR���p�C��
	void BasicVSCompile();
	// �s�N�Z���V�F�[�_�t�@�C���̓ǂݍ��݂ƃR���p�C��
	void BasicPSCompile();
	void BasicPSCompile2();
public:
	Microsoft::WRL::ComPtr<ID3DBlob> GetvsBlob();		 // ���_�V�F�[�_�I�u�W�F�N�g���擾����֐�
	Microsoft::WRL::ComPtr<ID3DBlob> GetpsBlob();		 // �s�N�Z���V�F�[�_�I�u�W�F�N�g���擾����֐�
	Microsoft::WRL::ComPtr<ID3DBlob> GetpsBlob2();		 // �s�N�Z���V�F�[�_�I�u�W�F�N�g���擾����֐�
	Microsoft::WRL::ComPtr<ID3DBlob> GeterrorBlob();					 // �G���[�I�u�W�F�N�g���擾����֐�
	D3D12_INPUT_ELEMENT_DESC* GetInputLayout();		// ���_���C�A�E�g���擾����֐�
	int GetInputLayoutSize();						// ���_���C�A�E�g�̗v�f�����擾����֐�

	static ShaderCompiler* GetInstance();
	static void DestroyInstance();
private:
	ShaderCompiler() = default;
	~ShaderCompiler() = default;

	ShaderCompiler(const ShaderCompiler&) = delete;
	ShaderCompiler& operator=(const ShaderCompiler&) = delete;
	ShaderCompiler(const ShaderCompiler&&) = delete;
	ShaderCompiler& operator=(const ShaderCompiler&&) = delete;
};