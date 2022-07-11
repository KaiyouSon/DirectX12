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

D3D12_GPU_DESCRIPTOR_HANDLE Texture::GetGpuHandle()
{
	return gpuHandle;
}
Vec2 Texture::GetTextureSize()
{
	return textureSize;
}
std::string Texture::GetTextureTag()
{
	return textureTag;
}

TextureList::~TextureList()
{
	for (int i = 0; i < textureList.size(); i++)
	{
		delete textureList[i];
	}
	textureList.clear();
}

void TextureList::AddTexture(Texture* texture, std::string tag)
{
	texture->SetTextureTag(tag);
	textureList.push_back(texture);
}
vector <string> TextureList::GetList()
{
	vector <string> tmp;
	for (int i = 0; i < textureList.size(); i++)
	{
		tmp.push_back(textureList[i]->GetTextureTag());
	}
	return tmp;
}
Texture* TextureList::GetTexture(string tag)
{
	for (int i = 0; i < textureList.size(); i++)
	{
		if (textureList[i]->GetTextureTag() == tag)
		{
			return textureList[i];
		}
	}
	return nullptr;
}

Texture* TextureList::GetTexture(const int& arrayNumber)
{
	return textureList[arrayNumber];
}

TextureList* gameTextureList = new TextureList;