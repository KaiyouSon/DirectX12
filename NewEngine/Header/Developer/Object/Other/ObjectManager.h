#pragma once
#include "NewEngine/Header/Developer/Object/Other/DrawManager.h"
#include <vector>
class ObjectManager
{
private:
	std::vector<GameObject*> gameObjectList;

private:
	void LoadObjectList();
	void LoadSpriteList();

	void SaveObjectList();
	void SaveSpriteList();

public:
	~ObjectManager();
	void CreateCube();
	void CreateSphere();
	void CreateMonkey();
	void CreateModel(const ModelData& modelData);
	void CreateSprite();
	void Update();
	void Draw3D();
	void Draw2DToBack();
	void Draw2DToForward();

	void DestroyGameObject(GameObject* gameObject);
	void DestroyModel(Object3D* object3D);
	void DestroySprite(Sprite* sprite);

	std::vector<GameObject*> GetGameObjectList();
	GameObject* GetGameObject(std::string objName);

	static ObjectManager* GetInstance();
	static void DestroyInstance();
private:
	ObjectManager() = default;
	ObjectManager(const ObjectManager&) = delete;
	ObjectManager& operator=(const ObjectManager&) = delete;
	ObjectManager(const ObjectManager&&) = delete;
	ObjectManager& operator=(const ObjectManager&&) = delete;
};

extern ObjectManager* objManager;