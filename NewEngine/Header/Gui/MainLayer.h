#pragma once
#include "NewEngine/Header/Gui/ILayer.h"
class MainLayer : public ILayer
{
public:
	void Initialize() override;
	void Update() override;
	Vec2 GetPos() override;
	Vec2 GetSize() override;

	static MainLayer* GetInstance();
	static void DestroyInstance();
private:
	MainLayer() = default;
	~MainLayer() = default;

	MainLayer(const MainLayer&) = delete;
	MainLayer& operator=(const MainLayer&) = delete;
	MainLayer(const MainLayer&&) = delete;
	MainLayer& operator=(const MainLayer&&) = delete;
};