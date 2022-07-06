#include "NewEngine/Header/Gui/InspectorLayer.h"
#include "NewEngine/Header/Gui/GuiManager.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "NewEngine/Header/Developer/Object/Other/GameObject.h"
#include "NewEngine/Header/Developer/Component/ComponentManager.h"
using namespace std;

void InspectorLayer::Initialize()
{
	size = { 480,WIN_HEIGHT };
	pos = { WIN_WIDTH - size.x,0 };

	isChangeObjName = false;
}
void InspectorLayer::Update()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar;
	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
	ImGui::Begin("Inspector", nullptr, window_flags);

	ShowMenuBar();
	ShowObjectList();
	ShowSpriteList();

	ImGui::End();
}

void InspectorLayer::ShowMenuBar()
{
	for (auto tmpObjectList : ObjectManager::GetInstance()->GetObjectList())
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				if (ImGui::BeginMenu("Add Component"))
				{
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
	}
}
void InspectorLayer::ShowObjectList()
{
	auto objList = ObjectManager::GetInstance()->GetObjectList();

	for (int i = 0; i < objList.size(); i++)
	{
		// 選択したオブジェクトのコンポネントをInspectorウィンドウに表示
		if (objList[i]->GetisShowDataToInspector())
		{
			// 表示フラグ
			ShowisShowFlag(*objList[i]);	ImGui::SameLine();

			// 名前
			ShowNameString(*objList[i]);

			// タグ
			ShowTagString(*objList[i]);	ImGui::Separator();

			// トランスフォームコンポネント
			ShowTransform(*objList[i]);	ImGui::Separator();

			// テクスチャーコンポネント
			ShowTexture(*objList[i]);	ImGui::Separator();
		}
	}
}
void InspectorLayer::ShowSpriteList()
{
	auto sprList = ObjectManager::GetInstance()->GetSpriteList();

	for (int i = 0; i < sprList.size(); i++)
	{
		// 選択したオブジェクトのコンポネントをInspectorウィンドウに表示
		if (sprList[i]->GetisShowDataToInspector())
		{
			// 表示フラグ
			ShowisShowFlag(*sprList[i]); ImGui::SameLine();

			// 名前
			ShowNameString(*sprList[i]);

			// タグ
			ShowTagString(*sprList[i]);	ImGui::Separator();

			// トランスフォームコンポネント
			ShowTransform(*sprList[i]);	ImGui::Separator();

			// テクスチャーコンポネント
			ShowTexture(*sprList[i]);	ImGui::Separator();
		}
	}

	//for (auto tmpSpriteList : ObjectManager::GetInstance()->GetSpriteList())
	//{
	//	// 選択したオブジェクトのコンポネントをInspectorウィンドウに表示
	//	if (tmpSpriteList->GetisShowDataToInspector())
	//	{
	//		// 表示フラグ
	//		ShowisShowFlag(*tmpSpriteList);
	//		ImGui::SameLine();

	//		// タグ
	//		//char tag[100] = {};
	//		//for (int i = 0; i < tmpSpriteList->GetName().size(); i++)
	//		//{
	//		//	tag[i] = tmpSpriteList->GetTag().c_str()[i];
	//		//}
	//		//ImGui::InputText("Name", tag, 100);
	//		//tmpSpriteList->SetTag(tag);

	//		// 描画フラグ
	//		bool flag = tmpSpriteList->GetLayer();
	//		ImGui::Checkbox("DrawToForward", &flag);
	//		tmpSpriteList->SetLayer(flag);

	//		if (ImGui::CollapsingHeader("Transform"))
	//		{
	//			// いったん置いとく
	//			float tmpPos[3] =
	//			{
	//				tmpSpriteList->GetComponent<Transform>()->pos.x,
	//				tmpSpriteList->GetComponent<Transform>()->pos.y,
	//				tmpSpriteList->GetComponent<Transform>()->pos.z,
	//			};
	//			float tmpRot[3] =
	//			{
	//				tmpSpriteList->GetComponent<Transform>()->rot.x,
	//				tmpSpriteList->GetComponent<Transform>()->rot.y,
	//				tmpSpriteList->GetComponent<Transform>()->rot.z,
	//			};
	//			float tmpScale[3] =
	//			{
	//				tmpSpriteList->GetComponent<Transform>()->scale.x,
	//				tmpSpriteList->GetComponent<Transform>()->scale.y,
	//				tmpSpriteList->GetComponent<Transform>()->scale.z,
	//			};

	//			//ImGui::Text("	x		  y		  z");
	//			ImGui::DragFloat3("Postion", tmpPos, 1);
	//			ImGui::DragFloat3("Rotation", tmpRot, 0.2);
	//			ImGui::DragFloat3("Scale", tmpScale, 0.01);

	//			tmpSpriteList->GetComponent<Transform>()->pos.x = tmpPos[0];
	//			tmpSpriteList->GetComponent<Transform>()->pos.y = tmpPos[1];
	//			tmpSpriteList->GetComponent<Transform>()->pos.z = tmpPos[2];

	//			tmpSpriteList->GetComponent<Transform>()->rot.x = tmpRot[0];
	//			tmpSpriteList->GetComponent<Transform>()->rot.y = tmpRot[1];
	//			tmpSpriteList->GetComponent<Transform>()->rot.z = tmpRot[2];

	//			tmpSpriteList->GetComponent<Transform>()->scale.x = tmpScale[0];
	//			tmpSpriteList->GetComponent<Transform>()->scale.y = tmpScale[1];
	//			tmpSpriteList->GetComponent<Transform>()->scale.z = tmpScale[2];
	//		}
	//		if (ImGui::CollapsingHeader("Texture"))
	//		{
	//			vector <string> tmpTags = gameTextureList->GetList();
	//			const char* tags[2056]{};
	//			for (int i = 0; i < 2056; i++)
	//			{
	//				if (tags[i] == NULL) tags[i] = " ";
	//			}
	//			for (int i = 0; i < tmpTags.size(); i++)
	//			{
	//				tags[i] = tmpTags[i].c_str();
	//			}
	//			static int tagCurrent = -1;
	//			static int item_current_idx = 0;
	//			for (int i = 0; i < 2056; i++)
	//			{
	//				if (tmpSpriteList->GetComponent<Texture>()->GetTextureTag() == tags[i])
	//					tagCurrent = i;
	//			}

	//			if (ImGui::Combo("Texture Tag Name", &tagCurrent, tags, 2056))
	//			{
	//				tmpSpriteList->SetTexture(*gameTextureList->GetTexture((tags[tagCurrent])));
	//			}
	//		}
	//		break;
	//	}
	//}
}

void InspectorLayer::ShowisShowFlag(GameObject& gameObject)
{
	bool isShow = gameObject.GetisShow();
	ImGui::Checkbox(" ", &isShow);
	gameObject.SetisShow(isShow);
}
void InspectorLayer::ShowNameString(GameObject& gameObject)
{
	char str[100] = {};
	for (int i = 0; i < gameObject.GetName().size(); i++)
	{
		str[i] = gameObject.GetName().c_str()[i];
	}
	if (ImGui::InputText("  ", str, 100) == true)
	{
		isChangeObjName = true;
	}
	gameObject.SetName(str);
}
void InspectorLayer::ShowTagString(GameObject& gameObject)
{
	ImGui::Text("Tag"); ImGui::SameLine();
	ImGui::Text(gameObject.GetComponent<Tag>()->GetTag().c_str()); ImGui::SameLine();

	if (ImGui::Button("   ", ImVec2(14, 14)))
		ImGui::OpenPopup("tagList");

	if (ImGui::BeginPopup("tagList"))
	{
		for (int i = 0; i < tagList->GetList().size(); i++)
		{
			if (ImGui::MenuItem(tagList->GetTag(i).c_str()))
			{
				gameObject.GetComponent<Tag>()->SetTag(tagList->GetTag(i));
			}
			ImGui::Separator();
		}
		ImGui::EndPopup();
	}
}
void InspectorLayer::ShowTransform(GameObject& gameObject)
{
	if (ImGui::CollapsingHeader("Transform"))
	{
		// いったん置いとく
		float tmpPos[3] =
		{
			gameObject.GetComponent<Transform>()->pos.x,
			gameObject.GetComponent<Transform>()->pos.y,
			gameObject.GetComponent<Transform>()->pos.z,
		};
		float tmpRot[3] =
		{
			gameObject.GetComponent<Transform>()->rot.x,
			gameObject.GetComponent<Transform>()->rot.y,
			gameObject.GetComponent<Transform>()->rot.z,
		};
		float tmpScale[3] =
		{
			gameObject.GetComponent<Transform>()->scale.x,
			gameObject.GetComponent<Transform>()->scale.y,
			gameObject.GetComponent<Transform>()->scale.z,
		};

		ImGui::DragFloat3("Postion", tmpPos, 0.05);
		ImGui::DragFloat3("Rotation", tmpRot, 0.2);
		ImGui::DragFloat3("Scale", tmpScale, 0.01);

		gameObject.GetComponent<Transform>()->pos.x = tmpPos[0];
		gameObject.GetComponent<Transform>()->pos.y = tmpPos[1];
		gameObject.GetComponent<Transform>()->pos.z = tmpPos[2];

		gameObject.GetComponent<Transform>()->rot.x = tmpRot[0];
		gameObject.GetComponent<Transform>()->rot.y = tmpRot[1];
		gameObject.GetComponent<Transform>()->rot.z = tmpRot[2];

		gameObject.GetComponent<Transform>()->scale.x = tmpScale[0];
		gameObject.GetComponent<Transform>()->scale.y = tmpScale[1];
		gameObject.GetComponent<Transform>()->scale.z = tmpScale[2];
	}
}
void InspectorLayer::ShowTexture(GameObject& gameObject)
{
	if (ImGui::CollapsingHeader("Texture"))
	{
		ImGui::Text("TextureTagName"); ImGui::SameLine();
		ImGui::Text(gameObject.GetComponent<Texture>()->GetTextureTag().c_str()); ImGui::SameLine();

		if (ImGui::Button("    ", ImVec2(14, 14)))
			ImGui::OpenPopup("gameTextureList");

		if (ImGui::BeginPopup("gameTextureList"))
		{
			for (int i = 0; i < gameTextureList->GetList().size(); i++)
			{
				if (ImGui::MenuItem(gameTextureList->GetTexture(i)->GetTextureTag().c_str()))
				{
					gameObject.GetComponent<Texture>()->SetTexture(gameTextureList->GetTexture(i));
				}
				ImGui::Separator();
			}
			ImGui::EndPopup();
		}
	}
}

Vec2 InspectorLayer::GetPos()
{
	return pos;
}
Vec2 InspectorLayer::GetSize()
{
	return size;
}

InspectorLayer* InspectorLayer::GetInstance()
{
	static InspectorLayer* InspectorLayer = new class::InspectorLayer;
	return InspectorLayer;
}
void InspectorLayer::DestroyInstance()
{
	delete GetInstance();
}
