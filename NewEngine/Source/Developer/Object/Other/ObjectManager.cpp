#include "NewEngine/Header/Developer/Object/Other/ObjectManager.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;

ObjectManager::~ObjectManager()
{
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		delete gameObjectList[i];
	}
}

void ObjectManager::CreateCube()
{
	int num = 0;

	Object3D* cubeModel = new Object3D;
	cubeModel->Initialize(modelDataList->GetModelData("cube"));
	cubeModel->SetName("Cube");
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		if (gameObjectList[i]->GetName() == cubeModel->GetName())
		{
			num += 1;
			cubeModel->SetName("Cube" + to_string(num));
		}
	}
	gameObjectList.push_back(cubeModel);
	cubeModel->SetModelType("Cube");
}
void ObjectManager::CreateSphere()
{
	int num = 0;

	Object3D* sphereModel = new Object3D;
	sphereModel->Initialize(modelDataList->GetModelData("sphere"));
	sphereModel->SetName("Sphere");
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		if (gameObjectList[i]->GetName() == sphereModel->GetName())
		{
			num += 1;
			sphereModel->SetName("Sphere" + to_string(num));
		}
	}
	gameObjectList.push_back(sphereModel);
	sphereModel->SetModelType("Sphere");
}
void ObjectManager::CreateMonkey()
{
	int num = 0;

	Object3D* monkeyModel = new Object3D;
	monkeyModel->Initialize(modelDataList->GetModelData("monkey"));
	monkeyModel->SetName("Monkey");
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		if (gameObjectList[i]->GetName() == monkeyModel->GetName())
		{
			num += 1;
			monkeyModel->SetName("Monkey" + to_string(num));
		}
	}
	gameObjectList.push_back(monkeyModel);
	monkeyModel->SetModelType("Monkey");
}
void ObjectManager::CreateModel(const ModelData& modelData)
{
	int num = 0;

	Object3D* model = new Object3D;
	model->Initialize(modelData);
	model->SetName("Model");
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		if (gameObjectList[i]->GetName() == model->GetName())
		{
			num += 1;
			model->SetName("Model" + to_string(num));
		}
	}
	gameObjectList.push_back(model);
	model->SetModelType("Model");
}
void ObjectManager::CreateSprite()
{
	int num = 0;

	Sprite* sprite = new Sprite;
	sprite->Initialize();
	sprite->SetName("Sprite");
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		if (gameObjectList[i]->GetName() == sprite->GetName())
		{
			num += 1;
			sprite->SetName("Sprite" + to_string(num));
		}
	}
	gameObjectList.push_back(sprite);
	sprite->SetModelType("Sprite");
}
void ObjectManager::DestroyGameObject(GameObject* gameObject)
{
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		if (gameObjectList[i] == gameObject)
		{
			delete gameObjectList[i];
			gameObjectList[i] = nullptr;
			gameObjectList.erase(gameObjectList.begin() + i);
		}
	}
}
void ObjectManager::DestroyModel(Object3D* object3D)
{
	//for (int i = 0; i < objectList.size(); i++)
	//{
	//	if (objectList[i] == object3D)
	//	{
	//		delete objectList[i];
	//		objectList[i] = nullptr;
	//		objectList.erase(objectList.begin() + i);
	//	}
	//}
}
void ObjectManager::DestroySprite(Sprite* sprite)
{
	//for (int i = 0; i < spriteList.size(); i++)
	//{
	//	if (spriteList[i] == sprite)
	//	{
	//		delete spriteList[i];
	//		spriteList[i] = nullptr;
	//		spriteList.erase(spriteList.begin() + i);
	//	}
	//}
}

void ObjectManager::Update()
{
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		switch (gameObjectList[i]->GetObjectType())
		{
		case Object3DType:
			dynamic_cast<Object3D*>(gameObjectList[i])->Update();
			break;

		case SpriteType:
			dynamic_cast<Sprite*>(gameObjectList[i])->Update();
			break;
		}
	}

}
void ObjectManager::Draw3D()
{
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		if (gameObjectList[i]->GetisShow() == true &&
			gameObjectList[i]->GetObjectType() == Object3DType)
		{
			dynamic_cast<Object3D*>(gameObjectList[i])->Draw();
		}
	}
}
void ObjectManager::Draw2DToBack()
{
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		if (gameObjectList[i]->GetisShow() == true &&
			gameObjectList[i]->GetObjectType() == SpriteType)
		{
			if (dynamic_cast<Sprite*>(gameObjectList[i])->GetLayer() == false)
				dynamic_cast<Sprite*>(gameObjectList[i])->Draw();
		}
	}
}
void ObjectManager::Draw2DToForward()
{
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		if (gameObjectList[i]->GetisShow() == true &&
			gameObjectList[i]->GetObjectType() == SpriteType)
		{
			if (dynamic_cast<Sprite*>(gameObjectList[i])->GetLayer() == true)
				dynamic_cast<Sprite*>(gameObjectList[i])->Draw();
		}
	}
}

std::vector<GameObject*> ObjectManager::GetGameObjectList()
{
	return gameObjectList;
}
GameObject* ObjectManager::GetGameObject(std::string objName)
{
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		if (gameObjectList[i]->GetName() == objName)
			return gameObjectList[i];
	}
	return nullptr;
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

ObjectManager* objManager = ObjectManager::GetInstance();