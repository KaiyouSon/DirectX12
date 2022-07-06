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
	cubeModel->SetModelType("Monkey");
}
void ObjectManager::CreateModel(const ModelData& modelData)
{
	Object3D* model = new Object3D;
	model->Initialize(modelData);
	objectList.push_back(model);
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
void ObjectManager::Draw3D()
{
	for (int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i]->GetisShow() == true)
			objectList[i]->Draw();
	}
}
void ObjectManager::Draw2DToBack()
{
	for (int i = 0; i < spriteList.size(); i++)
	{
		if (spriteList[i]->GetLayer() == false &&
			spriteList[i]->GetisShow() == true)
			spriteList[i]->Draw();
	}
}
void ObjectManager::Draw2DToForward()
{
	for (int i = 0; i < spriteList.size(); i++)
	{
		if (spriteList[i]->GetLayer() == true &&
			spriteList[i]->GetisShow() == true)
			spriteList[i]->Draw();
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

		string numberKey;
		for (int i = 0; i < listSize; i++)
		{
			numberKey = "Object" + to_string(i);
			// モデルタイプの読み込み
			if (key == numberKey + "ModelType")
			{
				string modelType;
				lineStream >> modelType;
				if (modelType == "Cube") CreateCube();
				if (modelType == "Sphere") CreateSphere();
				if (modelType == "Monkey") CreateMonkey();
			}

			if (key == numberKey + "Transform" + "pos")
			{
				lineStream >> objectList[i]->GetComponent<Transform>("Transform")->pos.x;
				lineStream >> objectList[i]->GetComponent<Transform>("Transform")->pos.y;
				lineStream >> objectList[i]->GetComponent<Transform>("Transform")->pos.z;
			}
			else if (key == numberKey + "Transform" + "rot")
			{
				lineStream >> objectList[i]->GetComponent<Transform>("Transform")->rot.x;
				lineStream >> objectList[i]->GetComponent<Transform>("Transform")->rot.y;
				lineStream >> objectList[i]->GetComponent<Transform>("Transform")->rot.z;
			}
			else if (key == numberKey + "Transform" + "scale")
			{
				lineStream >> objectList[i]->GetComponent<Transform>("Transform")->scale.x;
				lineStream >> objectList[i]->GetComponent<Transform>("Transform")->scale.y;
				lineStream >> objectList[i]->GetComponent<Transform>("Transform")->scale.z;
			}
			else if (key == numberKey + "TextureTag")
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

		string numberStr;
		for (int i = 0; i < listSize; i++)
		{
			numberStr = "Sprite" + to_string(i);

			if (key == numberStr)	CreateSprite();

			//	表示フラグ
			if (key == (numberStr + "isShow"))
			{
				bool isShow;
				lineStream >> isShow;
				spriteList[i]->SetisShow(isShow);
			}

			// レイヤー
			if (key == (numberStr + "Layer"))
			{
				bool layer;
				lineStream >> layer;
				spriteList[i]->SetLayer(layer);
			}

			if (key == numberStr + "Transform" + "pos")
			{
				lineStream >> spriteList[i]->GetComponent<Transform>("Transform")->pos.x;
				lineStream >> spriteList[i]->GetComponent<Transform>("Transform")->pos.y;
				lineStream >> spriteList[i]->GetComponent<Transform>("Transform")->pos.z;
			}
			else if (key == numberStr + "Transform" + "rot")
			{
				lineStream >> spriteList[i]->GetComponent<Transform>("Transform")->rot.x;
				lineStream >> spriteList[i]->GetComponent<Transform>("Transform")->rot.y;
				lineStream >> spriteList[i]->GetComponent<Transform>("Transform")->rot.z;
			}
			else if (key == numberStr + "Transform" + "scale")
			{
				lineStream >> spriteList[i]->GetComponent<Transform>("Transform")->scale.x;
				lineStream >> spriteList[i]->GetComponent<Transform>("Transform")->scale.y;
				lineStream >> spriteList[i]->GetComponent<Transform>("Transform")->scale.z;
			}
			else if (key == numberStr + "TextureTag")
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

	string numberStr;
	for (int i = 0; i < objectList.size(); i++)
	{
		numberStr = "Object" + to_string(i);
		// モデルのタイプ
		file << numberStr + "ModelType ";
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
				file << numberStr + "Transform" + "pos ";
				file << objectList[i]->GetComponent<Transform>("Transform")->pos.x << " ";
				file << objectList[i]->GetComponent<Transform>("Transform")->pos.y << " ";
				file << objectList[i]->GetComponent<Transform>("Transform")->pos.z << " ";
				file << "\n";
				file << numberStr + "Transform" + "rot ";
				file << objectList[i]->GetComponent<Transform>("Transform")->rot.x << " ";
				file << objectList[i]->GetComponent<Transform>("Transform")->rot.y << " ";
				file << objectList[i]->GetComponent<Transform>("Transform")->rot.z << " ";
				file << "\n";
				file << numberStr + "Transform" + "scale ";
				file << objectList[i]->GetComponent<Transform>("Transform")->scale.x << " ";
				file << objectList[i]->GetComponent<Transform>("Transform")->scale.y << " ";
				file << objectList[i]->GetComponent<Transform>("Transform")->scale.z << " ";
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

	string numberStr;
	for (int i = 0; i < spriteList.size(); i++)
	{
		numberStr = "Sprite" + to_string(i);

		// スプライト
		file << numberStr + "\n";
		// 表示フラグ
		file << numberStr + "isShow ";
		file << spriteList[i]->GetisShow();
		file << "\n";
		// 描画設定
		file << numberStr + "Layer ";
		file << spriteList[i]->GetLayer();
		file << "\n";
		// コンポネントリスト
		file << "ComponentListSize ";
		file << spriteList[i]->GetComponentList().size() << "\n";
		// コンポネントリストの中身
		for (int j = 0; j < spriteList[i]->GetComponentList().size(); j++)
		{
			// トランスフォーム
			if (spriteList[i]->GetComponentList()[j]->GetComponentName() == "Transform")
			{
				file << numberStr + "Transform" + "pos ";
				file << spriteList[i]->GetComponent<Transform>("Transform")->pos.x << " ";
				file << spriteList[i]->GetComponent<Transform>("Transform")->pos.y << " ";
				file << spriteList[i]->GetComponent<Transform>("Transform")->pos.z << " ";
				file << "\n";
				file << numberStr + "Transform" + "rot ";
				file << spriteList[i]->GetComponent<Transform>("Transform")->rot.x << " ";
				file << spriteList[i]->GetComponent<Transform>("Transform")->rot.y << " ";
				file << spriteList[i]->GetComponent<Transform>("Transform")->rot.z << " ";
				file << "\n";
				file << numberStr + "Transform" + "scale ";
				file << spriteList[i]->GetComponent<Transform>("Transform")->scale.x << " ";
				file << spriteList[i]->GetComponent<Transform>("Transform")->scale.y << " ";
				file << spriteList[i]->GetComponent<Transform>("Transform")->scale.z << " ";
				file << "\n";
			}

			if (spriteList[i]->GetComponentList()[j]->GetComponentName() == "Texture")
			{
				file << numberStr + "TextureTag ";
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
