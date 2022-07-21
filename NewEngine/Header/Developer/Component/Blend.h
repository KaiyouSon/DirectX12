#pragma once
#include "NewEngine/Header/Developer/Component/IComponent.h"

enum BlendMode
{
	Alpha3D,
	Add3D,
	Alpha2D,
	AlphaLine,
	AlphaRenderTexture,
};

class Blend : public IComponent
{
public:
	void SetBlendMode(int blendmode);
};
