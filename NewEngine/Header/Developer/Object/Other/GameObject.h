#pragma once
#include "NewEngine/Header/Developer/Component/IComponent.h"
#include <vector>
#include <string>

class GameObject
{
protected:
	std::string tag;
	bool isShowDataToInspector;
	std::vector<IComponent*> components;
public:
	GameObject();
	virtual ~GameObject();

	void SetTag(std::string tag);
	void SetisShowDataToInspector(bool isShowDataToInspector);

	std::string GetTag();
	bool GetisShowDataToInspector();

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