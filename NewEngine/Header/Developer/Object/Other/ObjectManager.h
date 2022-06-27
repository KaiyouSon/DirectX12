#pragma once
#include "NewEngine/Header/Developer/Object/Other/DrawManager.h"
#include <vector>
class ObjectManager
{
private:
	std::vector<Object3D*> objectList;

public:
	~ObjectManager();
	void CreateCube();
	void CreateSphere();
	void CreateMonkey();
	void CreateModel(const ModelData& modelData);
	void Update();
	void Draw2D();
	void Draw3D();

	void SetObjectList(std::vector<Object3D*> objectList);
	std::vector<Object3D*> GetObjectList();

	static ObjectManager* GetInstance();
	static void DestroyInstance();
private:
	ObjectManager() = default;
	ObjectManager(const ObjectManager&) = delete;
	ObjectManager& operator=(const ObjectManager&) = delete;
	ObjectManager(const ObjectManager&&) = delete;
	ObjectManager& operator=(const ObjectManager&&) = delete;
};