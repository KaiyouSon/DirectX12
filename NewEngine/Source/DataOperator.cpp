#include "NewEngine/Header/Developer/Object/Other/ObjectManager.h"
#include "NewEngine/Header/DataOperator.h"
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
}
void DataOperator::LoadData()
{
	LoadModelDataList();
}

// ゲームウィンドウデータ
void DataOperator::SaveWindowData()
{
	ofstream file;
	file.open("GameWindow.txt", std::ios::out);

	// タイトルの書き込み
	file << "GameWindowTitle ";
	file << gameWindowTitleForStorage.c_str();
	file << "\n";

	// サイズの書き込み
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
		// 1行分の文字列をストリームに変換して解析しやすくする
		istringstream lineStream(line);
		// 半角スペース区切りで行の先頭文字列を取得
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

// モデルデータリスト
void DataOperator::SaveModelDataList()
{
	ofstream file;
	file.open("ModelDataList.txt", std::ios::out);

	//サイズのセーブ
	file << "ListSize " << modelDataList->GetList().size() << "\n";

	string dataType;
	for (int i = 0; i < modelDataList->GetList().size(); i++)
	{
		if (i == 0) dataType = "Basic";
		if (i == 3) dataType = "Load";
		// ファイルパス
		file << dataType + "ModelDataFilePath ";
		file << modelDataList->GetList()[i].GetFilePath();
		file << "\n";

		// タグ
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
		// 1行分の文字列をストリームに変換して解析しやすくする
		istringstream lineStream(line);
		// 半角スペース区切りで行の先頭文字列を取得
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

bool DataOperator::CheckSaveData()
{
	if (ProcessMessage())
		ImGui::OpenPopup("CheckSaveDataWindow");

	if (ImGui::BeginPopupModal("CheckSaveDataWindow"))
	{
		ImGui::Text("Do you want to save data?");

		if (ImGui::Button("Save"))
		{
			ObjectManager::GetInstance()->SaveData();
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
