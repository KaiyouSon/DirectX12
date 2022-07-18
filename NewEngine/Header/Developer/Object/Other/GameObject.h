#pragma once
#include "NewEngine/Header/Developer/Component/IComponent.h"
#include "NewEngine/Header/Developer/Component/ComponentManager.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include <vector>
#include <string>

enum ObjectType
{
	Object3DType,
	SpriteType,
	RenderTextureType,
	LineType,
};

class GameObject
{
protected:
	std::string name;
	std::string modelType;
	int objectType;

	bool isShow;
	bool isShowDataToInspector;
	std::vector<IComponent*> componentList;

	Color color;

public:
	GameObject();
	virtual ~GameObject();

	void SetisShow(bool isShow);
	void SetName(std::string name);
	void SetColor(const Color& color);
	void SetModelType(std::string modelType);
	void SetisShowDataToInspector(bool isShowDataToInspector);
	void SetTexture(Texture& texture);

	int GetObjectType();
	bool GetisShow();
	std::string GetName();
	std::string GetModelType();
	Color GetColor();
	bool GetisShowDataToInspector();
	std::vector<IComponent*> GetComponentList();

	template<class T>
	T* GetComponent()
	{
		for (auto component : componentList) {
			T* currentComponent = dynamic_cast<T*>(component);
			if (currentComponent != nullptr) return currentComponent;
		}
		return nullptr;
	}
};