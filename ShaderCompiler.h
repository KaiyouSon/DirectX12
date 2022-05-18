#pragma once
#include <d3d12.h>
class ShaderCompiler
{
private:
	ID3DBlob* vsBlob = nullptr;		// ���_�V�F�[�_�I�u�W�F�N�g
	ID3DBlob* psBlob = nullptr;		// �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ID3DBlob* psBlob2 = nullptr;		// �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ID3DBlob* errorBlob = nullptr;	// �G���[�I�u�W�F�N�g
	D3D12_INPUT_ELEMENT_DESC inputLayout[3];	// ���_���C�A�E�g

public:
	// ���_�V�F�[�_�t�@�C���̓ǂݍ��݂ƃR���p�C��
	void BasicVSCompile();
	// �s�N�Z���V�F�[�_�t�@�C���̓ǂݍ��݂ƃR���p�C��
	void BasicPSCompile();
public:
	ID3DBlob* GetvsBlob();		 // ���_�V�F�[�_�I�u�W�F�N�g���擾����֐�
	ID3DBlob* GetpsBlob();		 // �s�N�Z���V�F�[�_�I�u�W�F�N�g���擾����֐�
	ID3DBlob* GetpsBlob2();		 // �s�N�Z���V�F�[�_�I�u�W�F�N�g���擾����֐�
	ID3DBlob** GeterrorBlobAddress();	 // �G���[�I�u�W�F�N�g���擾����֐�
	D3D12_INPUT_ELEMENT_DESC* GetInputLayout();		// ���_���C�A�E�g���擾����֐�
	int GetInputLayoutSize();						// ���_���C�A�E�g�̗v�f�����擾����֐�

	static ShaderCompiler& GetInstance();

private:
	ShaderCompiler() = default;
	~ShaderCompiler() = default;

	ShaderCompiler(const ShaderCompiler&) = delete;
	ShaderCompiler& operator=(const ShaderCompiler&) = delete;
	ShaderCompiler(const ShaderCompiler&&) = delete;
	ShaderCompiler& operator=(const ShaderCompiler&&) = delete;
};