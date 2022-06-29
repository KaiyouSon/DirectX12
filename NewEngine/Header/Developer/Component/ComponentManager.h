#pragma once
#include "NewEngine/Header/Developer/Component/IComponent.h"
#include <vector>

class ComponentManager
{
private:
	std::vector<IComponent*> table;

public:
	ComponentManager();
	~ComponentManager();



};

