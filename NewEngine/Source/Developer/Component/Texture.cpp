#include "NewEngine/Header/Developer/Component/Texture.h"
using namespace std;

Texture::Texture()
{
	componentName = "Texture";
}

void Texture::SetCpuHandle(D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle)
{
	this->cpuHandle = cpuHandle;
}
void Texture::SetGpuHandle(D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle)
{
	this->gpuHandle = gpuHandle;
}
void Texture::SetTextureSize(const Vec2& textureSize)
{
	this->textureSize = textureSize;
}
void Texture::SetTextureTag(string textureTag)
{
	this->textureTag = textureTag;
}
void Texture::SetTexture(Texture* texture)
{
	*this = *texture;
}

void Texture::SetFilePath(string filePath)
{
	this->filePath = filePath;
}

D3D12_GPU_DESCRIPTOR_HANDLE Texture::GetGpuHandle()
{
	return gpuHandle;
}
Vec2 Texture::GetTextureSize()
{
	return textureSize;
}
string Texture::GetTextureTag()
{
	return textureTag;
}

string Texture::GetFilePath()
{
	return filePath;
}

TextureList::~TextureList()
{
	for (int i = 0; i < list.size(); i++)
	{
		delete list[i];
	}
	list.clear();
}

void TextureList::AddTexture(Texture* texture, string tag)
{
	texture->SetTextureTag(tag);
	list.push_back(texture);
}
vector <Texture*> TextureList::GetList()
{
	return list;
}
Texture* TextureList::GetTexture(string tag)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i]->GetTextureTag() == tag)
		{
			return list[i];
		}
	}
	return nullptr;
}

TextureList* gameTextureList = new TextureList;