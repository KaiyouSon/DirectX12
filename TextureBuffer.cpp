#include "TextureBuffer.h"
#include "NewEngineBase.h"
#include <cassert>
#include <DirectXTex.h>
using namespace DirectX;
using namespace Microsoft::WRL;

TextureBuffer::~TextureBuffer()
{
	delete[] imageData;
}

void TextureBuffer::Initialize1()
{
	// �S�Ẵs�N�Z���̐F�̏�����
	for (size_t i = 0; i < imageDataCount; i++)
	{
		imageData[i].x = 1.0f;	// R
		imageData[i].y = 1.0f;	// G
		imageData[i].z = 1.0f;	// B
		imageData[i].w = 1.0f;	// A
	}

	// �q�[�v�̐ݒ�
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	textureHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	textureHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	textureHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC textureResourceDesc{};
	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureResourceDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureResourceDesc.Width = textureWidth; // ��
	textureResourceDesc.Height = textureWidth; // ����
	textureResourceDesc.DepthOrArraySize = 1;
	textureResourceDesc.MipLevels = 1;
	textureResourceDesc.SampleDesc.Count = 1;

	HRESULT result;

	// �e�N�X�`���o�b�t�@�̐���
	result = NewEngineBase::GetInstance().GetDevice()->
		CreateCommittedResource(
			&textureHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&textureResourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&texBuff));
	assert(SUCCEEDED(result));

	// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	result = texBuff->WriteToSubresource(
		0,
		nullptr, // �S�̈�փR�s�[
		imageData,	// ���f�[�^�A�h���X
		sizeof(Vec4) * textureWidth, // 1���C���T�C�Y
		sizeof(Vec4) * imageDataCount // �S�T�C�Y
	);
}

void TextureBuffer::Initialize2(const wchar_t* szFile)
{
	HRESULT result;

	// �摜�t�@�C���̗p��
	TexMetadata metadata{};
	ScratchImage scratchImg{};
	// WIC�e�N�X�`���̃��[�h
	result = LoadFromWICFile(
		szFile,
		WIC_FLAGS_NONE,
		&metadata, scratchImg);

	if (result != S_OK) Initialize1();

	if (result == S_OK)
	{
		ScratchImage mipChain{};
		// �~�b�v�}�b�v����
		result = GenerateMipMaps(
			scratchImg.GetImages(), scratchImg.GetImageCount(), scratchImg.GetMetadata(),
			TEX_FILTER_DEFAULT, 0, mipChain);
		if (SUCCEEDED(result))
		{
			scratchImg = std::move(mipChain);
			metadata = scratchImg.GetMetadata();
		}

		// �ǂݍ��񂾃f�B�t���[�Y�e�N�X�`����SRGB�Ƃ��Ĉ���
		metadata.format = MakeSRGB(metadata.format);

		// �q�[�v�̐ݒ�
		D3D12_HEAP_PROPERTIES textureHeapProp{};
		textureHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
		textureHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
		textureHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;

		// ���\�[�X�ݒ�
		D3D12_RESOURCE_DESC textureResourceDesc{};
		textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		textureResourceDesc.Format = metadata.format;
		textureResourceDesc.Width = metadata.width; // ��
		textureResourceDesc.Height = (UINT)metadata.height; // ����
		textureResourceDesc.DepthOrArraySize = (UINT16)metadata.arraySize;
		textureResourceDesc.MipLevels = (UINT16)metadata.mipLevels;
		textureResourceDesc.SampleDesc.Count = 1;

		// �e�N�X�`���o�b�t�@�̐���
		result = NewEngineBase::GetInstance().GetDevice()->
			CreateCommittedResource(
				&textureHeapProp,
				D3D12_HEAP_FLAG_NONE,
				&textureResourceDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&texBuff));
		assert(SUCCEEDED(result));

		// �S�~�b�v�}�b�v�ɂ���
		for (size_t i = 0; i < metadata.mipLevels; i++)
		{
			// �S�~�b�v�}�b�v���x�����w�肵�ăC���[�W���擾
			const Image* img = scratchImg.GetImage(i, 0, 0);
			// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
			result = texBuff->WriteToSubresource(
				(UINT)i,
				nullptr,				// �S�̈�փR�s�[
				img->pixels,			// ���f�[�^�A�h���X
				(UINT)img->rowPitch,	// �P���C���T�C�Y
				(UINT)img->slicePitch	// �P���T�C�Y
			);
			assert(SUCCEEDED(result));
		}
	}
}

ComPtr<ID3D12Resource> TextureBuffer::GetTextureBuff()
{
	return texBuff;
}