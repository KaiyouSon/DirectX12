#include "NewEngine/Header/Developer/Object/Other/ObjectManager.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
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
	cubeModel->SetModelType("Cube");
}

void ObjectManager::CreateSphere()
{
	Object3D* cubeModel = new Object3D;
	cubeModel->Initialize(sphere);
	objectList.push_back(cubeModel);
	cubeModel->SetTag("Sphere");
	cubeModel->SetModelType("Sphere");
}

void ObjectManager::CreateMonkey()
{
	Object3D* cubeModel = new Object3D;
	cubeModel->Initialize(monkey);
	objectList.push_back(cubeModel);
	cubeModel->SetTag("Monkey");
	cubeModel->SetModelType("Monkey");
}

void ObjectManager::CreateModel(const ModelData& modelData)
{
	Object3D* model = new Object3D;
	model->Initialize(modelData);
	objectList.push_back(model);
	model->SetTag("model");
	model->SetModelType("model");
}

void ObjectManager::Update()
{
	for (int i = 0; i < objectList.size(); i++)
	{
		objectList[i]->Update();

		if (objectList[i] == nullptr) objectList.erase(objectList.begin() + i);
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

void ObjectManager::DestroyModel(Object3D* object3D)
{
	for (int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i] == object3D)
		{
			delete objectList[i];
			objectList[i] == nullptr;
			objectList.erase(objectList.begin() + i);
		}
	}
}

void ObjectManager::LoadData()
{
	ifstream file;
	string filename = "ObjectListData.txt";
	file.open(filename);
	string line;
	string objKey;
	int listSize = 0;
	while (getline(file, line))
	{
		// 1行分の文字列をストリームに変換して解析しやすくする
		istringstream lineStream(line);
		// 半角スペース区切りで行の先頭文字列を取得
		string key;
		getline(lineStream, key, ' ');

		if (key == "ObjectListSize")
		{
			lineStream >> listSize;
			//objectList.resize(listSize);
		}

		for (int i = 0; i < listSize; i++)
		{
			if (key == "Object" + to_string(i) + "ModelType")
			{
				string modelType;
				lineStream >> modelType;
				if (modelType == "Cube") CreateCube();
				if (modelType == "Sphere") CreateSphere();
				if (modelType == "Monkey") CreateMonkey();
			}

			if (key == "Object" + to_string(i) + "Transform" + "pos")
			{
				lineStream >> objectList[i]->GetComponent<Transform>("Transform")->pos.x;
				lineStream >> objectList[i]->GetComponent<Transform>("Transform")->pos.y;
				lineStream >> objectList[i]->GetComponent<Transform>("Transform")->pos.z;
			}
			else if (key == "Object" + to_string(i) + "Transform" + "rot")
			{
				lineStream >> objectList[i]->GetComponent<Transform>("Transform")->rot.x;
				lineStream >> objectList[i]->GetComponent<Transform>("Transform")->rot.y;
				lineStream >> objectList[i]->GetComponent<Transform>("Transform")->rot.z;
			}
			else if (key == "Object" + to_string(i) + "Transform" + "scale")
			{
				lineStream >> objectList[i]->GetComponent<Transform>("Transform")->scale.x;
				lineStream >> objectList[i]->GetComponent<Transform>("Transform")->scale.y;
				lineStream >> objectList[i]->GetComponent<Transform>("Transform")->scale.z;
			}
		}
	}

	file.close();
}

void ObjectManager::SaveData()
{
	ofstream file;
	string filename = "ObjectListData.txt";
	file.open(filename, std::ios::out);
	//リストのサイズをセーブ
	file << "ObjectListSize " << objectList.size() << "\n";
	for (int i = 0; i < objectList.size(); i++)
	{
		// モデルのタイプ
		file << "Object" + to_string(i) + "ModelType ";
		file << objectList[i]->GetModelType() << "\n";
		// トランスフォーム
		{
			Vec3 pos = objectList[i]->GetComponent<Transform>("Transform")->pos;
			Vec3 rot = objectList[i]->GetComponent<Transform>("Transform")->rot;
			Vec3 scale = objectList[i]->GetComponent<Transform>("Transform")->scale;

			file << "Object" + to_string(i) + "Transform" + "pos ";
			file << pos.x << " ";
			file << pos.y << " ";
			file << pos.z << " ";
			file << "\n";
			file << "Object" + to_string(i) + "Transform" + "rot ";
			file << rot.x << " ";
			file << rot.y << " ";
			file << rot.z << " ";
			file << "\n";
			file << "Object" + to_string(i) + "Transform" + "scale ";
			file << scale.x << " ";
			file << scale.y << " ";
			file << scale.z << " ";
			file << "\n";
		}
	}
	file.close();
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
