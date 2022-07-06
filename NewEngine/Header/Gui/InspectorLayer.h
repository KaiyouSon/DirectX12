#pragma once
#include "NewEngine/Header/Gui/ILayer.h"
#include "NewEngine//Header/Developer/Object/Other/ObjectManager.h"
class InspectorLayer : public ILayer
{
private:
	void ShowMenuBar();
	void ShowObjectList();
	void ShowSpriteList();

	void ShowisShowFlag(GameObject& gameObject);
	void ShowNameString(GameObject& gameObject);
	void ShowTagString(GameObject& gameObject);
	void ShowDrawLayer(Sprite& sprite);
	void ShowTransform(GameObject& gameObject);
	void ShowTexture(GameObject& gameObject);

public:
	bool isChangeObjName;

	void Initialize() override;
	void Update() override;

	Vec2 GetPos() override;
	Vec2 GetSize() override;

	static InspectorLayer* GetInstance();
	static void DestroyInstance();
private:
	InspectorLayer() = default;
	~InspectorLayer() = default;

	InspectorLayer(const InspectorLayer&) = delete;
	InspectorLayer& operator=(const InspectorLayer&) = delete;
	InspectorLayer(const InspectorLayer&&) = delete;
	InspectorLayer& operator=(const InspectorLayer&&) = delete;
};

