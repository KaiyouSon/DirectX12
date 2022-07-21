#pragma once
#include "NewEngine/Header/Developer/Component/IComponent.h"
#include "NewEngine/Header/Developer/Math/MathUtil.h"
#include <d3d12.h>
#include <wrl.h>
#include <memory>
#include <vector>
#include <string>

class Texture : public IComponent
{
private:
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = D3D12_CPU_DESCRIPTOR_HANDLE(); //SRVのハンドル(CPU側)
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = D3D12_GPU_DESCRIPTOR_HANDLE(); //SRVのハンドル(GPU側)
	Vec2 textureSize;
	std::string textureTag;
	std::string filePath;
public:
	Microsoft::WRL::ComPtr<ID3D12Resource> buffer; //テクスチャのリソース
	Texture();
	void SetCpuHandle(D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle);
	void SetGpuHandle(D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle);
	void SetTextureSize(const Vec2& textureSize);
	void SetTextureTag(std::string textureTag);
	void SetTexture(Texture* texture);
	void SetFilePath(std::string filePath);

	D3D12_GPU_DESCRIPTOR_HANDLE GetGpuHandle();
	Vec2 GetTextureSize();
	std::string GetTextureTag();
	std::string GetFilePath();
};

class TextureList
{
private:
	std::vector<Texture*> list;

public:
	~TextureList();
	void AddTexture(Texture* texture, std::string tag);
	std::vector <Texture*> GetList();

	Texture* GetTexture(std::string tag);
};

extern std::unique_ptr<TextureList> gameTextureList;
