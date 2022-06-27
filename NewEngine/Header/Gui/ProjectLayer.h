#pragma once
#include "NewEngine/Header/Gui/ILayer.h"
#include <filesystem>
class ProjectLayer : public ILayer
{
private:
	const char* projectDirectroy;
	std::filesystem::path currentDirectroy;

public:
	void Initialize() override;
	void Update() override;
	Vec2 GetPos() override;
	Vec2 GetSize() override;

	static ProjectLayer* GetInstance();
	static void DestroyInstance();

private:
	ProjectLayer() = default;
	~ProjectLayer() = default;

	ProjectLayer(const ProjectLayer&) = delete;
	ProjectLayer& operator=(const ProjectLayer&) = delete;
	ProjectLayer(const ProjectLayer&&) = delete;
	ProjectLayer& operator=(const ProjectLayer&&) = delete;
};

