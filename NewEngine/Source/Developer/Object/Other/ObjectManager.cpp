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

	for (int i = 0; i < spriteList.size(); i++)
	{
		delete spriteList[i];
	}
}

void ObjectManager::CreateCube()
{
	int num = 0;

	Object3D* cubeModel = new Object3D;
	cubeModel->Initialize(cube);
	cubeModel->SetName("Cube");
	for (int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i]->GetName() == cubeModel->GetName())
		{
			num += 1;
			cubeModel->SetName("Cube" + to_string(num));
		}
	}
	objectList.push_back(cubeModel);
	cubeModel->SetTag("Cube");
	cubeModel->SetModelType("Cube");
}
void ObjectManager::CreateSphere()
{
	int num = 0;

	Object3D* cubeModel = new Object3D;
	cubeModel->Initialize(sphere);
	cubeModel->SetName("Sphere");
	for (int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i]->GetName() == cubeModel->GetName())
		{
			num += 1;
			cubeModel->SetName("Sphere" + to_string(num));
		}
	}
	objectList.push_back(cubeModel);
	cubeModel->SetTag("Sphere");
	cubeModel->SetModelType("Sphere");
}
void ObjectManager::CreateMonkey()
{
	int num = 0;

	Object3D* cubeModel = new Object3D;
	cubeModel->Initialize(monkey);
	cubeModel->SetName("Monkey");
	for (int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i]->GetName() == cubeModel->GetName())
		{
			num += 1;
			cubeModel->SetName("Monkey" + to_string(num));
		}
	}
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
void ObjectManager::CreateSprite()
{
	int num = 0;

	Sprite* sprite = new Sprite;
	sprite->Initialize();
	sprite->SetName("Sprite");
	for (int i = 0; i < spriteList.size(); i++)
	{
		if (spriteList[i]->GetName() == sprite->GetName())
		{
			num += 1;
			sprite->SetName("Sprite" + to_string(num));
		}
	}
	spriteList.push_back(sprite);
	sprite->SetTag("Sprite");
	sprite->SetModelType("Sprite");
}
void ObjectManager::DestroyModel(Object3D* object3D)
{
	for (int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i] == object3D)
		{
			delete objectList[i];
			objectList[i] = nullptr;
			objectList.erase(objectList.begin() + i);
		}
	}
}
void ObjectManager::DestroySprite(Sprite* sprite)
{
	for (int i = 0; i < spriteList.size(); i++)
	{
		if (spriteList[i] == sprite)
		{
			delete spriteList[i];
			spriteList[i] = nullptr;
			spriteList.erase(spriteList.begin() + i);
		}
	}
}

void ObjectManager::Update()
{
	for (int i = 0; i < objectList.size(); i++)
	{
		objectList[i]->Update();
	}

	for (int i = 0; i < spriteList.size(); i++)
	{
		spriteList[i]->Update();
	}
}
void ObjectManager::Draw2D()
{
	for (int i = 0; i < spriteList.size(); i++)
	{
		spriteList[i]->Draw();
	}
}
void ObjectManager::Draw3D()
{
	for (int i = 0; i < objectList.size(); i++)
	{
		objectList[i]->Draw();
	}
}

void ObjectManager::LoadData()
{
	LoadObjectList();
	LoadSpriteList();
}
void ObjectManager::SaveData()
{
	SaveObjectList();
	SaveSpriteList();
}

void ObjectManager::LoadObjectList()
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
		}

		for (int i = 0; i < listSize; i++)
		{
			// モデルタイプの読み込み
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
			else if (key == "Object" + to_string(i) + "TextureTag")
			{
				string tmpTag;
				lineStream >> tmpTag;
				if (tmpTag != "")
					objectList[i]->SetTexture(*gameTextureList->GetTexture(tmpTag));
			}
		}
	}

	file.close();
}
void ObjectManager::LoadSpriteList()
{
	ifstream file;
	string filename = "SpriteListData.txt";
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

		if (key == "SpriteListSize")
		{
			lineStream >> listSize;
		}

		for (int i = 0; i < listSize; i++)
		{
			if (key == "Sprite" + to_string(i))	CreateSprite();

			if (key == "Sprite" + to_string(i) + "Transform" + "pos")
			{
				lineStream >> spriteList[i]->GetComponent<Transform>("Transform")->pos.x;
				lineStream >> spriteList[i]->GetComponent<Transform>("Transform")->pos.y;
				lineStream >> spriteList[i]->GetComponent<Transform>("Transform")->pos.z;
			}
			else if (key == "Sprite" + to_string(i) + "Transform" + "rot")
			{
				lineStream >> spriteList[i]->GetComponent<Transform>("Transform")->rot.x;
				lineStream >> spriteList[i]->GetComponent<Transform>("Transform")->rot.y;
				lineStream >> spriteList[i]->GetComponent<Transform>("Transform")->rot.z;
			}
			else if (key == "Sprite" + to_string(i) + "Transform" + "scale")
			{
				lineStream >> spriteList[i]->GetComponent<Transform>("Transform")->scale.x;
				lineStream >> spriteList[i]->GetComponent<Transform>("Transform")->scale.y;
				lineStream >> spriteList[i]->GetComponent<Transform>("Transform")->scale.z;
			}
			else if (key == "Sprite" + to_string(i) + "TextureTag")
			{
				string tmpTag;
				lineStream >> tmpTag;
				if (tmpTag != "")
					spriteList[i]->SetTexture(*gameTextureList->GetTexture(tmpTag));
			}
		}
	}

	file.close();
}
void ObjectManager::SaveObjectList()
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
		// コンポネントリスト
		file << "ComponentListSize ";
		file << objectList[i]->GetComponentList().size() << "\n";
		// コンポネントリストの中身
		for (int j = 0; j < objectList[i]->GetComponentList().size(); j++)
		{
			// トランスフォーム
			if (objectList[i]->GetComponentList()[j]->GetComponentName() == "Transform")
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

			if (objectList[i]->GetComponentList()[j]->GetComponentName() == "Texture")
			{
				file << "Object" + to_string(i) + "TextureTag ";
				string tmp = objectList[i]->GetComponent<Texture>("Texture")->GetTextureTag();
				file << objectList[i]->GetComponent<Texture>("Texture")->GetTextureTag();
				file << "\n";
			}
		}
	}
	file.close();
}
void ObjectManager::SaveSpriteList()
{
	ofstream file;
	string filename = "SpriteListData.txt";
	file.open(filename, std::ios::out);
	//リストのサイズをセーブ
	file << "SpriteListSize " << spriteList.size() << "\n";
	for (int i = 0; i < spriteList.size(); i++)
	{
		// モデルのタイプ
		file << "Sprite" + to_string(i) + "\n";
		// コンポネントリスト
		file << "ComponentListSize ";
		file << spriteList[i]->GetComponentList().size() << "\n";
		// コンポネントリストの中身
		for (int j = 0; j < spriteList[i]->GetComponentList().size(); j++)
		{
			// トランスフォーム
			if (spriteList[i]->GetComponentList()[j]->GetComponentName() == "Transform")
			{
				Vec3 pos = spriteList[i]->GetComponent<Transform>("Transform")->pos;
				Vec3 rot = spriteList[i]->GetComponent<Transform>("Transform")->rot;
				Vec3 scale = spriteList[i]->GetComponent<Transform>("Transform")->scale;

				file << "Sprite" + to_string(i) + "Transform" + "pos ";
				file << pos.x << " ";
				file << pos.y << " ";
				file << pos.z << " ";
				file << "\n";
				file << "Sprite" + to_string(i) + "Transform" + "rot ";
				file << rot.x << " ";
				file << rot.y << " ";
				file << rot.z << " ";
				file << "\n";
				file << "Sprite" + to_string(i) + "Transform" + "scale ";
				file << scale.x << " ";
				file << scale.y << " ";
				file << scale.z << " ";
				file << "\n";
			}

			if (spriteList[i]->GetComponentList()[j]->GetComponentName() == "Texture")
			{
				file << "Sprite" + to_string(i) + "TextureTag ";
				string tmp = spriteList[i]->GetComponent<Texture>("Texture")->GetTextureTag();
				file << spriteList[i]->GetComponent<Texture>("Texture")->GetTextureTag();
				file << "\n";
			}
		}
	}
	file.close();
}

std::vector<Object3D*> ObjectManager::GetObjectList()
{
	return objectList;
}
std::vector<Sprite*> ObjectManager::GetSpriteList()
{
	return spriteList;
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
