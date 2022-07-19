#pragma once
#include "NewEngine/Header/Developer/Component/IComponent.h"

enum BlendMode
{
	Alpha3D,
	Add3D,
	Alpha2D,
	AddLine,
};

class Blend : public IComponent
{
public:
	void SetBlendMode(BlendMode blendmode);
};
