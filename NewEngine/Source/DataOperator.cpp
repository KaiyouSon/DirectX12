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

void DataOperator::SaveWindowData()
{
	ofstream file;
	string filename = "GameWindow.txt";
	file.open(filename, std::ios::out);

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
