#pragma once
#include "NewEngine/Gui/Header/ILayer.h"
class SceneLayer : public ILayer
{
public:
	void Initialize() override;
	void Update() override;
	Vec2 GetPos() override;
	Vec2 GetSize() override;

	static SceneLayer* GetInstance();
	static void DestroyInstance();
private:
	SceneLayer() = default;
	~SceneLayer() = default;

	SceneLayer(const SceneLayer&) = delete;
	SceneLayer& operator=(const SceneLayer&) = delete;
	SceneLayer(const SceneLayer&&) = delete;
	SceneLayer& operator=(const SceneLayer&&) = delete;
};