#pragma once
#include "Header/GUI/ILayer.h"
class ProjectLayer : public ILayer
{
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

