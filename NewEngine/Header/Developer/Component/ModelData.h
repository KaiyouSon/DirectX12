#pragma once
#include "NewEngine/Header/Developer/Component/IComponent.h"
#include "NewEngine/Header/Render/Buffer/VertexBuffer.h"
#include <vector>
#include <string>

struct ModelData : public IComponent
{
private:
	std::string tag;
	std::string filePath;
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned short> indices;

	void SetModelData(const ModelData& modelData);
	void SetTag(std::string tag);
	void SetFilePath(std::string filePath);
	std::string GetTag();
	std::string GetFilePath();
};

class ModelDataList
{
private:
	std::vector<ModelData> list;

public:
	void AddModelData(ModelData& modelData, const std::string& tag);
	void DestoryModelData(const std::string& tag);

	std::vector<ModelData> GetList();
	ModelData GetModelData(const std::string& tag);

	static ModelDataList* GetInstance();
	static void DestroyInstance();
private:
	ModelDataList();
	~ModelDataList() = default;

	ModelDataList(const ModelDataList&) = delete;
	ModelDataList& operator=(const ModelDataList&) = delete;
	ModelDataList(const ModelDataList&&) = delete;
	ModelDataList& operator=(const ModelDataList&&) = delete;
};

extern ModelDataList* modelDataList;