#pragma once
#include "NewEngine/Header/Developer/Object/Other/DrawManager.h"
#include <vector>
class ObjectManager
{
private:
	std::vector<Object3D*> modelList;

public:
	~ObjectManager();
	void CreateCube();
	void CreateSphere();
	void CreateMonkey();
	void Update();
	void Draw2D();
	void Draw3D();

	static ObjectManager* GetInstance();
	static void DestroyInstance();
private:
	ObjectManager() = default;
	ObjectManager(const ObjectManager&) = delete;
	ObjectManager& operator=(const ObjectManager&) = delete;
	ObjectManager(const ObjectManager&&) = delete;
	ObjectManager& operator=(const ObjectManager&&) = delete;
};