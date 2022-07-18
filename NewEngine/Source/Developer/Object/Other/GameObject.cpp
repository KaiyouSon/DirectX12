#include "NewEngine/Header/Developer/Object/Other/GameObject.h"
#include "NewEngine/Header/Developer/Component/ComponentManager.h"
using namespace std;

GameObject::GameObject() :
	isShow(true),
	isShowDataToInspector(false)
{
	// デフォルトで持っているコンポネント

	// タグ
	Tag* tag = new Tag;
	componentList.push_back(tag);

	// トランスフォーム
	Transform* transform = new Transform;
	componentList.push_back(transform);

	// テクスチャー
	Texture* texture = new Texture;
	componentList.push_back(texture);

	// モデルデータ
	ModelData* modelData = new ModelData;
	componentList.push_back(modelData);

	Blend* blend = new Blend;
	componentList.push_back(blend);
}

GameObject::~GameObject()
{
	for (int i = 0; i < componentList.size(); i++)
	{
		delete componentList[i];
	}
}

void GameObject::SetisShow(bool isShow)
{
	this->isShow = isShow;
}
void GameObject::SetName(std::string name)
{
	this->name = name;
}
void GameObject::SetColor(const Color& color)
{
	this->color = color;
}
void GameObject::SetModelType(std::string modelType)
{
	this->modelType = modelType;
}
void GameObject::SetisShowDataToInspector(bool isShowDataToInspector)
{
	this->isShowDataToInspector = isShowDataToInspector;
}

void GameObject::SetTexture(Texture& texture)
{
	GetComponent<Texture>()->SetTexture(&texture);
}

int GameObject::GetObjectType()
{
	return objectType;
}
bool GameObject::GetisShow()
{
	return isShow;
}
string GameObject::GetName()
{
	return name;
}
string GameObject::GetModelType()
{
	return modelType;
}
Color GameObject::GetColor()
{
	return color;
}
bool GameObject::GetisShowDataToInspector()
{
	return isShowDataToInspector;
}

vector<IComponent*> GameObject::GetComponentList()
{
	return componentList;
}
