#pragma once
#include "NewEngine/Header/Developer/Component/IComponent.h"
#include <vector>
#include <string>

class GameObject
{
protected:
	std::string name;
	std::string modelType;
	bool isShow;
	bool isShowDataToInspector;
	std::vector<IComponent*> components;

public:
	GameObject();
	virtual ~GameObject();

	void SetisShow(bool isShow);
	void SetName(std::string name);
	void SetModelType(std::string modelType);
	void SetisShowDataToInspector(bool isShowDataToInspector);

	bool GetisShow();
	std::string GetName();
	std::string GetModelType();
	bool GetisShowDataToInspector();
	std::vector<IComponent*> GetComponentList();

	template<class T>
	T* GetComponent()
	{
		for (auto component : components) {
			T* currentComponent = dynamic_cast<T*>(component);
			if (currentComponent != nullptr) return currentComponent;
		}
		return nullptr;
	}
};