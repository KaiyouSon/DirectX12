#include "NewEngine/Header/Developer/Object/Other/GameObject.h"
#include "NewEngine/Header/Developer/Component/Transform.h"
using namespace std;

GameObject::GameObject() :
	isShowDataToInspector(false)
{
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

void GameObject::SetisShowDataToInspector(bool isShowDataToInspector)
{
	this->isShowDataToInspector = isShowDataToInspector;
}

string GameObject::GetTag()
{
	return tag;
}

bool GameObject::GetisShowDataToInspector()
{
	return isShowDataToInspector;
}