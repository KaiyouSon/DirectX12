#include "NewEngine/Header/Developer/Component/ModelData.h"
#include "NewEngine/Header/Developer/Object/Other/DrawManager.h"
using namespace std;

void ModelData::SetModelData(const ModelData& modelData) { *this = modelData; }
void ModelData::SetTag(std::string tag) { this->tag = tag; }
void ModelData::SetFilePath(std::string filePath) { this->filePath = filePath; }
string ModelData::GetTag() { return tag; }
string ModelData::GetFilePath() { return filePath; }

ModelDataList::ModelDataList()
{
	ModelData cube = LoadModel("NewEngine/BasicModel/cube.obj");		// óßï˚ëÃ
	ModelData sphere = LoadModel("NewEngine/BasicModel/sphere.obj");	// ãÖëÃ
	ModelData monkey = LoadModel("NewEngine/BasicModel/monkey.obj");	// ÉÇÉìÉLÅ[

	cube.SetTag("cube");			list.push_back(cube);
	sphere.SetTag("sphere");		list.push_back(sphere);
	monkey.SetTag("monkey");		list.push_back(monkey);
}
void ModelDataList::AddModelData(ModelData& modelData, const string& tag)
{
	modelData.SetTag(tag);
	list.push_back(modelData);
}
void ModelDataList::DestoryModelData(const std::string& tag)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].GetTag() == tag)
		{
			list.erase(list.begin() + i);
			break;
		}
	}
}
ModelData ModelDataList::GetModelData(const std::string& tag)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].GetTag() == tag)
		{
			return list[i];
		}
	}
}
vector<ModelData> ModelDataList::GetList() { return list; }

ModelDataList* ModelDataList::GetInstance()
{
	static ModelDataList* modelDataList = new ModelDataList;
	return modelDataList;
}
void ModelDataList::DestroyInstance()
{
	delete GetInstance();
}

ModelDataList* modelDataList = ModelDataList::GetInstance();