#include "NewEngine/Header/Developer/Component/ComponentManager.h"
#include "NewEngine/Header/Developer/Component/Texture.h"
#include "NewEngine/Header/Developer/Component/Transform.h"

ComponentManager::ComponentManager()
{
	Texture* texture = new Texture;
	table.push_back(texture);

	Transform* transform = new Transform;
	table.push_back(transform);
}

ComponentManager::~ComponentManager()
{
	for (int i = 0; i < table.size(); i++)
	{
		delete table[i];
	}
}
