#pragma once
#include "NewEngine/Header/Developer/Component/IComponent.h"
#include <vector>
#include <string>

class GameObject
{
protected:
	std::string tag;
	std::string name;
	std::string modelType;
	bool isShowDataToInspector;
	std::vector<IComponent*> components;

public:
	GameObject();
	virtual ~GameObject();

	void SetTag(std::string tag);
	void SetName(std::string name);
	void SetModelType(std::string modelType);
	void SetisShowDataToInspector(bool isShowDataToInspector);

	std::string GetTag();
	std::string GetName();
	std::string GetModelType();
	bool GetisShowDataToInspector();
	std::vector<IComponent*> GetComponentList();

	template<class T>
	T* GetComponent(std::string componentName)
	{
		for (int i = 0; i < components.size(); i++)
		{
			if (components[i]->GetComponentName() == componentName)
			{
				T* component = dynamic_cast<T*> (components[i]);
				return component;
			}
		}
		return nullptr;
	}
};