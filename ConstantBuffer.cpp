#include "ConstantBuffer.h"
#include "NewEngineBase.h"

#include <cassert>

void ConstantBuffer::MaterialBufferInit()
{
	// �q�[�v�̐ݒ�
	D3D12_HEAP_PROPERTIES cbHeapProp{};
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	// GPU�ւ̓]���p
	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC cbResourceDesc{};
	cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourceDesc.Width = (sizeof(ConstBufferDateMaterial) + 0xff) & ~0xff; // 256�o�C�g�A���C�������g
	cbResourceDesc.Height = 1;
	cbResourceDesc.DepthOrArraySize = 1;
	cbResourceDesc.MipLevels = 1;
	cbResourceDesc.SampleDesc.Count = 1;
	cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	HRESULT result;

	// �萔�o�b�t�@�̐���
	result = NewEngineBase::GetInstance().GetDevice()->
		CreateCommittedResource(
			&cbHeapProp,	// �q�[�v�̐ݒ�
			D3D12_HEAP_FLAG_NONE,
			&cbResourceDesc, // ���\�[�X�̐ݒ�
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&constBuffMaterial));
	assert(SUCCEEDED(result));

	// �萔�o�b�t�@�̃}�b�s���O
	ConstBufferDateMaterial* constMapMaterial = nullptr;
	result = constBuffMaterial->Map(0, nullptr, (void**)&constMapMaterial);	// �}�b�s���O
	assert(SUCCEEDED(result));

	// �l���������ނƎ����I�ɓ]�������
	constMapMaterial->color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

void ConstantBuffer::TransformBufferInit()
{
	// �q�[�v�̐ݒ�
	D3D12_HEAP_PROPERTIES cbHeapProp{};
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	// GPU�ւ̓]���p
	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC cbResourceDesc{};
	cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourceDesc.Width = (sizeof(ConstBufferDataTransform) + 0xff) & ~0xff; // 256�o�C�g�A���C�������g
	cbResourceDesc.Height = 1;
	cbResourceDesc.DepthOrArraySize = 1;
	cbResourceDesc.MipLevels = 1;
	cbResourceDesc.SampleDesc.Count = 1;
	cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	HRESULT result;

	// �萔�o�b�t�@�̐���
	result = NewEngineBase::GetInstance().GetDevice()->
		CreateCommittedResource(
			&cbHeapProp,	// �q�[�v�̐ݒ�
			D3D12_HEAP_FLAG_NONE,
			&cbResourceDesc, // ���\�[�X�̐ݒ�
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&constBuffTransform));
	assert(SUCCEEDED(result));

	// �萔�o�b�t�@�̃}�b�s���O
	result = constBuffTransform->Map(0, nullptr, (void**)&constMapTransform);	// �}�b�s���O
	assert(SUCCEEDED(result));
}

ID3D12Resource* ConstantBuffer::GetConstBuffMaterial()
{
	return constBuffMaterial;
}

ID3D12Resource* ConstantBuffer::GetConstBuffTransform()
{
	return constBuffTransform;
}

void ConstantBuffer::SetColor(const Vec4& color)
{
	HRESULT result;

	// �萔�o�b�t�@�̃}�b�s���O
	ConstBufferDateMaterial* constMapMaterial = nullptr;
	result = constBuffMaterial->Map(0, nullptr, (void**)&constMapMaterial);	// �}�b�s���O
	assert(SUCCEEDED(result));

	// �l���������ނƎ����I�ɓ]�������
	constMapMaterial->color = Vec4(
		color.x / 255,
		color.y / 255,
		color.z / 255,
		color.w / 255);	// RGBA
}
