#include "NewEngine/Header/Render/Buffer/TextureBuffer.h"
#include "NewEngine/Header/Render/RenderBase.h"
#include <cassert>
using namespace std;
using namespace DirectX;
using namespace Microsoft::WRL;

Vec4* TextureBuffer::imageData = new Vec4[imageDataCount];

TextureBuffer::~TextureBuffer()
{
	delete[] imageData;
}

// �e�N�X�`���̃��[�h
Texture* TextureBuffer::LoadTexture(const string filePath)
{
	HRESULT result;
	Texture* texture = new Texture;
	TexMetadata metadata{};
	ScratchImage scratchImg{};
	wstring wfilePath(filePath.begin(), filePath.end());

	// WIC�e�N�X�`���̃��[�h
	result = LoadFromWICFile(
		wfilePath.c_str(),
		WIC_FLAGS_NONE,
		&metadata, scratchImg);
	assert(SUCCEEDED(result));

	// �~�b�v�}�b�v����
	ScratchImage mipChain{};
	result = GenerateMipMaps(
		scratchImg.GetImages(),
		scratchImg.GetImageCount(),
		scratchImg.GetMetadata(),
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

	// �e�N�X�`���̃T�C�Y���Z�b�g
	texture->SetTextureSize(Vec2(textureResourceDesc.Width, textureResourceDesc.Height));

	// �e�N�X�`���o�b�t�@�̐���
	result = RenderBase::GetInstance()->GetDevice()->
		CreateCommittedResource(
			&textureHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&textureResourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&texture->buffer));
	assert(SUCCEEDED(result));

	// �S�~�b�v�}�b�v�ɂ���
	for (size_t i = 0; i < metadata.mipLevels; i++)
	{
		// �S�~�b�v�}�b�v���x�����w�肵�ăC���[�W���擾
		const Image* img = scratchImg.GetImage(i, 0, 0);
		// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
		result = texture->buffer->WriteToSubresource(
			(UINT)i,
			nullptr,				// �S�̈�փR�s�[
			img->pixels,			// ���f�[�^�A�h���X
			(UINT)img->rowPitch,	// �P���C���T�C�Y
			(UINT)img->slicePitch	// �P���T�C�Y
		);
		assert(SUCCEEDED(result));
	}

	RenderBase::GetInstance()->CreateSrv(*texture, textureResourceDesc);

	texture->buffer->SetName(L"Texture");

	return texture;
}

// �f�t�H���g�̃e�N�X�`��
Texture TextureBuffer::GetDefaultTexture()
{
	HRESULT result;
	Texture texture;

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

	// �e�N�X�`���̃T�C�Y���Z�b�g
	texture.SetTextureSize(Vec2(textureResourceDesc.Width, textureResourceDesc.Height));

	// �e�N�X�`���o�b�t�@�̐���
	result = RenderBase::GetInstance()->GetDevice()->
		CreateCommittedResource(
			&textureHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&textureResourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&texture.buffer));
	assert(SUCCEEDED(result));

	// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	result = texture.buffer->WriteToSubresource(
		0,
		nullptr, // �S�̈�փR�s�[
		imageData,	// ���f�[�^�A�h���X
		sizeof(Vec4) * textureWidth, // 1���C���T�C�Y
		sizeof(Vec4) * imageDataCount // �S�T�C�Y
	);

	RenderBase::GetInstance()->CreateSrv(texture, textureResourceDesc);

	return texture;
}

void TextureBuffer::UnLoadTexture(Texture* texture)
{
	delete texture;
}
