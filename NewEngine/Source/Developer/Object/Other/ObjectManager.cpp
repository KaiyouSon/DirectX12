#include "NewEngine/Header/Developer/Object/Other/ObjectManager.h"
#include <vector>
using namespace std;

ObjectManager::~ObjectManager()
{
	for (int i = 0; i < objectList.size(); i++)
	{
		delete objectList[i];
	}
}

void ObjectManager::CreateCube()
{
	Object3D* cubeModel = new Object3D;
	cubeModel->Initialize(cube);
	objectList.push_back(cubeModel);
	cubeModel->SetTag("Cube");
}

void ObjectManager::CreateSphere()
{
	Object3D* cubeModel = new Object3D;
	cubeModel->Initialize(sphere);
	objectList.push_back(cubeModel);
	cubeModel->SetTag("Sphere");
}

void ObjectManager::CreateMonkey()
{
	Object3D* cubeModel = new Object3D;
	cubeModel->Initialize(monkey);
	objectList.push_back(cubeModel);
	cubeModel->SetTag("Monkey");
}

void ObjectManager::CreateModel(const ModelData& modelData)
{
	Object3D* model = new Object3D;
	model->Initialize(modelData);
	objectList.push_back(model);
	model->SetTag("model");
}

void ObjectManager::Update()
{
	for (int i = 0; i < objectList.size(); i++)
	{
		objectList[i]->Update();
	}
}

void ObjectManager::Draw2D()
{
}

void ObjectManager::Draw3D()
{
	for (int i = 0; i < objectList.size(); i++)
	{
		objectList[i]->Draw();
	}
}

void ObjectManager::SetObjectList(std::vector<Object3D*> objectList)
{
	this->objectList = objectList;
}

std::vector<Object3D*> ObjectManager::GetObjectList()
{
	return objectList;
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
