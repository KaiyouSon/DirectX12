#pragma once
#include "NewEngine/Header/Developer/Object/Other/DrawManager.h"
#include <vector>
class ObjectManager
{
private:
	std::vector<Object3D*> objectList;
	std::vector<Sprite*> spriteList;

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
	void Draw2D();
	void Draw3D();

	void DestroyModel(Object3D* object3D);
	void DestroySprite(Sprite* sprite);

	void LoadData();
	void SaveData();

	std::vector<Object3D*> GetObjectList();
	std::vector<Sprite*> GetSpriteList();

	static ObjectManager* GetInstance();
	static void DestroyInstance();
private:
	ObjectManager() = default;
	ObjectManager(const ObjectManager&) = delete;
	ObjectManager& operator=(const ObjectManager&) = delete;
	ObjectManager(const ObjectManager&&) = delete;
	ObjectManager& operator=(const ObjectManager&&) = delete;
};