#pragma once
#include "NewEngine/Header/Developer/Component/Blend.h"
#include "NewEngine/Header/Developer/Component/Collider.h"
#include "NewEngine/Header/Developer/Component/IComponent.h"
#include "NewEngine/Header/Developer/Component/ModelData.h"
#include "NewEngine/Header/Developer/Component/Tag.h"
#include "NewEngine/Header/Developer/Component/Texture.h"
#include "NewEngine/Header/Developer/Component/Transform.h"
#include <vector>

class ComponentManager
{
private:
	std::vector<IComponent*> table;

public:
	ComponentManager();
	~ComponentManager();
};

