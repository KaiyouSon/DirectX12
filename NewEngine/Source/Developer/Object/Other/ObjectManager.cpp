#include "NewEngine/Header/Developer/Object/Other/ObjectManager.h"
#include <vector>
using namespace std;

ObjectManager::~ObjectManager()
{
	for (int i = 0; i < modelList.size(); i++)
	{
		delete modelList[i];
	}
}

void ObjectManager::CreateCube()
{
	Object3D* cubeModel = new Object3D;
	cubeModel->Initialize(cube);
	modelList.push_back(cubeModel);
}

void ObjectManager::CreateSphere()
{
	Object3D* cubeModel = new Object3D;
	cubeModel->Initialize(sphere);
	modelList.push_back(cubeModel);
}

void ObjectManager::CreateMonkey()
{
	Object3D* cubeModel = new Object3D;
	cubeModel->Initialize(monkey);
	modelList.push_back(cubeModel);
}

void ObjectManager::Update()
{
	for (int i = 0; i < modelList.size(); i++)
	{
		modelList[i]->Update();
	}
}

void ObjectManager::Draw2D()
{
}

void ObjectManager::Draw3D()
{
	for (int i = 0; i < modelList.size(); i++)
	{
		modelList[i]->Draw();
	}
}

ObjectManager* ObjectManager::GetInstance()
{
	static ObjectManager* objManager = new ObjectManager;
	return objManager;
}

void ObjectManager::DestroyInstance()
{
	delete GetInstance();
}
