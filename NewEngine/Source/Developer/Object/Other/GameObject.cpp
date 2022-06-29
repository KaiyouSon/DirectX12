#include "NewEngine/Header/Developer/Object/Other/GameObject.h"
#include "NewEngine/Header/Developer/Component/Transform.h"
#include "NewEngine/Header/Developer/Component/Texture.h"
using namespace std;

GameObject::GameObject() :
	isShowDataToInspector(false)
{
	Texture* texture = new Texture;
	components.push_back(texture);

	Transform* transform = new Transform;
	components.push_back(transform);
}

GameObject::~GameObject()
{
	for (int i = 0; i < components.size(); i++)
	{
		delete components[i];
	}
}

void GameObject::SetTag(string tag)
{
	this->tag = tag;
}

void GameObject::SetModelType(std::string modelType)
{
	this->modelType = modelType;
}

void GameObject::SetisShowDataToInspector(bool isShowDataToInspector)
{
	this->isShowDataToInspector = isShowDataToInspector;
}

string GameObject::GetTag()
{
	return tag;
}

std::string GameObject::GetModelType()
{
	return modelType;
}

bool GameObject::GetisShowDataToInspector()
{
	return isShowDataToInspector;
}

vector<IComponent*> GameObject::GetComponentList()
{
	return components;
}
