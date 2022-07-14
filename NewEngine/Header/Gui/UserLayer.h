#pragma once
#include "NewEngine/Header/Gui/ILayer.h"
class UserLayer : public ILayer
{
private:
	void ShowGameWindwoSetting();
	void ShowModelDataListSetting();

public:
	void Initialize() override;
	void Update() override;
	Vec2 GetPos() override;
	Vec2 GetSize() override;

	static UserLayer* GetInstance();
	static void DestroyInstance();
private:
	UserLayer() = default;
	~UserLayer() = default;

	UserLayer(const UserLayer&) = delete;
	UserLayer& operator=(const UserLayer&) = delete;
	UserLayer(const UserLayer&&) = delete;
	UserLayer& operator=(const UserLayer&&) = delete;
};

