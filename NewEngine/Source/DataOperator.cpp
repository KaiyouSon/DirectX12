#include "NewEngine/Header/DataOperator.h"
#include "NewEngine/Header/Developer/Object/Other/ObjectManager.h"
#include "NewEngine/Header/Gui/UserLayer.h"
#include "NewEngine/NewEngine.h"
#include "ImGUI/imgui.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;

void DataOperator::Initialize()
{
	gameWindowTitleForStorage = "erreo";
	gameWindowSizeForStorage = { 600,400 };
}

void DataOperator::SaveData()
{
	SaveModelDataList();
	SaveTextureList();
	SaveGameObjectList();
}
void DataOperator::LoadData()
{
	LoadModelDataList();
	LoadTextureList();
	LoadGameObjectList();
}

// �Q�[���E�B���h�E�f�[�^
void DataOperator::SaveWindowData()
{
	ofstream file;
	file.open("GameWindow.txt", std::ios::out);

	// �^�C�g���̏�������
	file << "GameWindowTitle ";
	file << gameWindowTitleForStorage.c_str();
	file << "\n";

	// �T�C�Y�̏�������
	file << "GameWindowSize ";
	file << gameWindowSizeForStorage.x << " ";
	file << gameWindowSizeForStorage.y << " ";
	file << "\n";

	file.close();
}
void DataOperator::LoadWindowData()
{
	ifstream file;
	file.open("GameWindow.txt");
	string line;

	while (getline(file, line))
	{
		// 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		istringstream lineStream(line);
		// ���p�X�y�[�X��؂�ōs�̐擪��������擾
		string key;
		getline(lineStream, key, ' ');

		if (key == "GameWindowTitle")
		{
			lineStream >> gameWindowTitleForStorage;
			continue;
		}
		if (key == "GameWindowSize")
		{
			lineStream >> gameWindowSizeForStorage.x;
			lineStream >> gameWindowSizeForStorage.y;
			continue;
		}
	}
	file.close();
}

// ���f���f�[�^���X�g
void DataOperator::SaveModelDataList()
{
	ofstream file;
	file.open("ModelDataList.txt", std::ios::out);

	//�T�C�Y�̃Z�[�u
	file << "ListSize " << modelDataList->GetList().size() << "\n";

	string dataType;
	for (int i = 0; i < modelDataList->GetList().size(); i++)
	{
		if (i == 0) dataType = "Basic";
		if (i == 3) dataType = "Load";
		// �t�@�C���p�X
		file << dataType + "ModelDataFilePath ";
		file << modelDataList->GetList()[i].GetFilePath();
		file << "\n";

		// �^�O
		file << dataType + "ModelDataTag ";
		file << modelDataList->GetList()[i].GetTag();
		file << "\n";
	}
	file.close();
}
void DataOperator::LoadModelDataList()
{
	ifstream file;
	file.open("ModelDataList.txt");
	string line;
	ModelData model;
	int listSize = 0;
	while (getline(file, line))
	{
		// 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		istringstream lineStream(line);
		// ���p�X�y�[�X��؂�ōs�̐擪��������擾
		string key;
		getline(lineStream, key, ' ');

		if (key == "ListSize")	lineStream >> listSize;

		if (key == "LoadModelDataFilePath")
		{
			string filePath;
			lineStream >> filePath;

			model = LoadModel(filePath.c_str());
			continue;
		}
		if (key == "LoadModelDataTag")
		{
			string tag;
			lineStream >> tag;

			modelDataList->AddModelData(model, tag);
			continue;
		}
	}
	file.close();
}

// �e�N�X�`���[���X�g
void DataOperator::SaveTextureList()
{
	ofstream file;
	file.open("TextureList.txt", std::ios::out);

	//�T�C�Y�̃Z�[�u
	file << "ListSize " << gameTextureList->GetList().size() << "\n";

	string dataType;
	for (int i = 0; i < gameTextureList->GetList().size(); i++)
	{
		// �t�@�C���p�X
		file << dataType + "TextureFilePath ";
		file << gameTextureList->GetList()[i]->GetFilePath();
		file << "\n";

		// �^�O
		file << dataType + "TextureTag ";
		file << gameTextureList->GetList()[i]->GetTextureTag();
		file << "\n";
	}
	file.close();
}
void DataOperator::LoadTextureList()
{
	ifstream file;
	file.open("TextureList.txt");
	string line;
	Texture* texture = nullptr;
	int listSize = 0;
	while (getline(file, line))
	{
		// 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		istringstream lineStream(line);
		// ���p�X�y�[�X��؂�ōs�̐擪��������擾
		string key;
		getline(lineStream, key, ' ');

		if (key == "ListSize")	lineStream >> listSize;

		if (key == "TextureFilePath")
		{
			string filePath;
			lineStream >> filePath;

			texture = LoadTexture(filePath.c_str());
			continue;
		}
		if (key == "TextureTag")
		{
			string tag;
			lineStream >> tag;

			gameTextureList->AddTexture(texture, tag);
			continue;
		}
	}
	file.close();
}

// �Q�[���I�u�W�F�N�g���X�g
void DataOperator::SaveGameObjectList()
{
	auto objList = objManager->GetGameObjectList();

	ofstream file;
	file.open("GameObjectList.txt", std::ios::out);
	//���X�g�̃T�C�Y���Z�[�u
	file << "GameObjectListSize " << objList.size() << "\n";

	string numberStr;
	for (int i = 0; i < objList.size(); i++)
	{
		numberStr = "GameObject" + to_string(i);
		if (objList[i]->GetObjectType() == ObjectType::Object3DType)
		{
			// ���f���f�[�^�̃^�O
			file << numberStr + "ModelDataTag ";
			file << objList[i]->GetComponent<ModelData>()->GetTag() << "\n";

			// �I�u�W�F�N�g�̖��O
			file << numberStr + "Name ";
			file << objList[i]->GetName() << "\n";

			// �R���|�l���g���X�g
			file << "ComponentListSize ";
			file << objList[i]->GetComponentList().size() << "\n";
			// �R���|�l���g���X�g�̒��g
			for (int j = 0; j < objList[i]->GetComponentList().size(); j++)
			{
				// �g�����X�t�H�[��
				if (objList[i]->GetComponentList()[j]->GetComponentName() == "Transform")
				{
					file << numberStr + "Transform" + "pos ";
					file << objList[i]->GetComponent<Transform>()->pos.x << " ";
					file << objList[i]->GetComponent<Transform>()->pos.y << " ";
					file << objList[i]->GetComponent<Transform>()->pos.z << " ";
					file << "\n";
					file << numberStr + "Transform" + "rot ";
					file << objList[i]->GetComponent<Transform>()->rot.x << " ";
					file << objList[i]->GetComponent<Transform>()->rot.y << " ";
					file << objList[i]->GetComponent<Transform>()->rot.z << " ";
					file << "\n";
					file << numberStr + "Transform" + "scale ";
					file << objList[i]->GetComponent<Transform>()->scale.x << " ";
					file << objList[i]->GetComponent<Transform>()->scale.y << " ";
					file << objList[i]->GetComponent<Transform>()->scale.z << " ";
					file << "\n";
				}

				// �e�N�X�`��
				if (objList[i]->GetComponentList()[j]->GetComponentName() == "Texture")
				{
					file << numberStr + "TextureTag ";
					string tmp = objList[i]->GetComponent<Texture>()->GetTextureTag();
					file << objList[i]->GetComponent<Texture>()->GetTextureTag();
					file << "\n";
				}
			}
		}
		if (objList[i]->GetObjectType() == ObjectType::SpriteType)
		{
			// �X�v���C�g
			file << numberStr + "Sprite" + "\n";

			// �I�u�W�F�N�g�̖��O
			file << numberStr + "Name ";
			file << objList[i]->GetName() << "\n";

			// �\���t���O
			file << numberStr + "isShow ";
			file << objList[i]->GetisShow();
			file << "\n";

			// �`��ݒ�
			file << numberStr + "Layer ";
			file << dynamic_cast<Sprite*>(objList[i])->GetLayer();
			file << "\n";

			// �R���|�l���g���X�g
			file << "ComponentListSize ";
			file << objList[i]->GetComponentList().size() << "\n";

			// �R���|�l���g���X�g�̒��g
			for (int j = 0; j < objList[i]->GetComponentList().size(); j++)
			{
				// �g�����X�t�H�[��
				if (objList[i]->GetComponentList()[j]->GetComponentName() == "Transform")
				{
					file << numberStr + "Transform" + "pos ";
					file << objList[i]->GetComponent<Transform>()->pos.x << " ";
					file << objList[i]->GetComponent<Transform>()->pos.y << " ";
					file << objList[i]->GetComponent<Transform>()->pos.z << " ";
					file << "\n";
					file << numberStr + "Transform" + "rot ";
					file << objList[i]->GetComponent<Transform>()->rot.x << " ";
					file << objList[i]->GetComponent<Transform>()->rot.y << " ";
					file << objList[i]->GetComponent<Transform>()->rot.z << " ";
					file << "\n";
					file << numberStr + "Transform" + "scale ";
					file << objList[i]->GetComponent<Transform>()->scale.x << " ";
					file << objList[i]->GetComponent<Transform>()->scale.y << " ";
					file << objList[i]->GetComponent<Transform>()->scale.z << " ";
					file << "\n";
				}

				if (objList[i]->GetComponentList()[j]->GetComponentName() == "Texture")
				{
					file << numberStr + "TextureTag ";
					string tmp = objList[i]->GetComponent<Texture>()->GetTextureTag();
					file << objList[i]->GetComponent<Texture>()->GetTextureTag();
					file << "\n";
				}
			}
		}
	}
	file.close();
}
void DataOperator::LoadGameObjectList()
{
	ifstream file;
	file.open("GameObjectList.txt");
	string line;
	int listSize = 0;
	while (getline(file, line))
	{
		auto objList = objManager->GetGameObjectList();

		// 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		istringstream lineStream(line);
		// ���p�X�y�[�X��؂�ōs�̐擪��������擾
		string key;
		getline(lineStream, key, ' ');

		// GameObjectList�̃T�C�Y
		if (key == "GameObjectListSize") lineStream >> listSize;

		string numberStr;
		for (int i = 0; i < listSize; i++)
		{
			numberStr = "GameObject" + to_string(i);

			// ���f���f�[�^�̃^�O
			if (key == numberStr + "ModelDataTag")
			{
				string modelDataTag;
				lineStream >> modelDataTag;
				objManager->CreateModel(modelDataList->GetModelData(modelDataTag));
				break;
			}

			if (key == numberStr + "Sprite") { objManager->CreateSprite();	break; }

			// �I�u�W�F�N�g�̖��O
			if (key == numberStr + "Name")
			{
				string tmpName;
				lineStream >> tmpName;
				objList[i]->SetName(tmpName);
				break;
			}

			//	�\���t���O
			if (key == numberStr + "isShow")
			{
				bool isShow;
				lineStream >> isShow;
				objList[i]->SetisShow(isShow);
				break;
			}

			// ���C���[
			if (key == numberStr + "Layer")
			{
				bool layer;
				lineStream >> layer;
				dynamic_cast<Sprite*>(objList[i])->SetLayer(layer);
				break;
			}

			// �g�����X�t�H�[��
			if (key == numberStr + "Transform" + "pos")
			{
				lineStream >> objList[i]->GetComponent<Transform>()->pos.x;
				lineStream >> objList[i]->GetComponent<Transform>()->pos.y;
				lineStream >> objList[i]->GetComponent<Transform>()->pos.z;
				break;
			}
			else if (key == numberStr + "Transform" + "rot")
			{
				lineStream >> objList[i]->GetComponent<Transform>()->rot.x;
				lineStream >> objList[i]->GetComponent<Transform>()->rot.y;
				lineStream >> objList[i]->GetComponent<Transform>()->rot.z;
				break;
			}
			else if (key == numberStr + "Transform" + "scale")
			{
				lineStream >> objList[i]->GetComponent<Transform>()->scale.x;
				lineStream >> objList[i]->GetComponent<Transform>()->scale.y;
				lineStream >> objList[i]->GetComponent<Transform>()->scale.z;
				break;
			}
			// �e�N�X�`���[
			else if (key == numberStr + "TextureTag")
			{
				string tmpTag;
				lineStream >> tmpTag;
				if (tmpTag != "")
					objList[i]->GetComponent<Texture>()->
					SetTexture(gameTextureList->GetTexture(tmpTag));
				break;
			}
		}
	}

	file.close();
}

bool DataOperator::CheckSaveData()
{
	if (ProcessMessage())
		ImGui::OpenPopup("CheckSaveDataWindow");

	if (ImGui::BeginPopupModal("CheckSaveDataWindow"))
	{
		ImGui::Text("Do you want to save data?");

		if (ImGui::Button("Save"))
		{
			DataOperator::GetInstance()->SaveData();
			return true;
		}
		if (ImGui::Button("Don't Save")) return true;
		if (ImGui::Button("Cancel")) return false;

		ImGui::EndPopup();
	}
}
void DataOperator::SetGameWindowParameter(std::string title, Vec2 size)
{
	gameWindowTitleForStorage = title;
	gameWindowSizeForStorage = size;
}

std::string DataOperator::GetGameWindowTitleForStorage()
{
	return gameWindowTitleForStorage;
}
Vec2 DataOperator::GetGameWindowSizeForStorage()
{
	return gameWindowSizeForStorage;
}

DataOperator* DataOperator::GetInstance()
{
	static DataOperator* dataOperator = new DataOperator;
	return dataOperator;
}
void DataOperator::DestroyInstance()
{
	delete GetInstance();
}
