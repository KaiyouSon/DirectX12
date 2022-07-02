#include "NewEngine/Header/Gui/InspectorLayer.h"
#include "NewEngine/Header/Gui/GuiManager.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "NewEngine/Header/Developer/Object/Other/ObjectManager.h"
#include "NewEngine/Header/Developer/Object/Other/GameObject.h"
using namespace std;

void InspectorLayer::Initialize()
{
	size = { 480,WIN_HEIGHT };
	pos = { WIN_WIDTH - size.x,0 };
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
	for (auto tmpObjectList : ObjectManager::GetInstance()->GetObjectList())
	{
		// �I�������I�u�W�F�N�g�̃R���|�l���g��Inspector�E�B���h�E�ɕ\��
		if (tmpObjectList->GetisShowDataToInspector())
		{
			ImGui::Text(tmpObjectList->GetName().c_str());
			if (ImGui::CollapsingHeader("Transform"))
			{
				// ��������u���Ƃ�
				float tmpPos[3] =
				{
					tmpObjectList->GetComponent<Transform>("Transform")->pos.x,
					tmpObjectList->GetComponent<Transform>("Transform")->pos.y,
					tmpObjectList->GetComponent<Transform>("Transform")->pos.z,
				};
				float tmpRot[3] =
				{
					tmpObjectList->GetComponent<Transform>("Transform")->rot.x,
					tmpObjectList->GetComponent<Transform>("Transform")->rot.y,
					tmpObjectList->GetComponent<Transform>("Transform")->rot.z,
				};
				float tmpScale[3] =
				{
					tmpObjectList->GetComponent<Transform>("Transform")->scale.x,
					tmpObjectList->GetComponent<Transform>("Transform")->scale.y,
					tmpObjectList->GetComponent<Transform>("Transform")->scale.z,
				};

				//ImGui::Text("	x		  y		  z");
				ImGui::DragFloat3("Postion", tmpPos, 0.05);
				ImGui::DragFloat3("Rotation", tmpRot, 0.2);
				ImGui::DragFloat3("Scale", tmpScale, 0.01);

				tmpObjectList->GetComponent<Transform>("Transform")->pos.x = tmpPos[0];
				tmpObjectList->GetComponent<Transform>("Transform")->pos.y = tmpPos[1];
				tmpObjectList->GetComponent<Transform>("Transform")->pos.z = tmpPos[2];

				tmpObjectList->GetComponent<Transform>("Transform")->rot.x = tmpRot[0];
				tmpObjectList->GetComponent<Transform>("Transform")->rot.y = tmpRot[1];
				tmpObjectList->GetComponent<Transform>("Transform")->rot.z = tmpRot[2];

				tmpObjectList->GetComponent<Transform>("Transform")->scale.x = tmpScale[0];
				tmpObjectList->GetComponent<Transform>("Transform")->scale.y = tmpScale[1];
				tmpObjectList->GetComponent<Transform>("Transform")->scale.z = tmpScale[2];
			}
			if (ImGui::CollapsingHeader("Texture"))
			{
				vector <string> tmpTags = gameTextureList->GetAllTextureTag();
				const char* tags[2056]{};
				for (int i = 0; i < 2056; i++)
				{
					if (tags[i] == NULL) tags[i] = " ";
				}
				for (int i = 0; i < tmpTags.size(); i++)
				{
					tags[i] = tmpTags[i].c_str();
				}
				static int tagCurrent = -1;
				static int item_current_idx = 0;
				for (int i = 0; i < 2056; i++)
				{
					if (tmpObjectList->GetComponent<Texture>("Texture")->GetTextureTag() == tags[i])
						tagCurrent = i;
				}

				if (ImGui::Combo("Texture Tag Name", &tagCurrent, tags, 2056))
				{
					tmpObjectList->SetTexture(*gameTextureList->GetTexture((tags[tagCurrent])));
				}
			}
			break;
		}
	}
}
void InspectorLayer::ShowSpriteList()
{
	for (auto tmpSpriteList : ObjectManager::GetInstance()->GetSpriteList())
	{
		// �I�������I�u�W�F�N�g�̃R���|�l���g��Inspector�E�B���h�E�ɕ\��
		if (tmpSpriteList->GetisShowDataToInspector())
		{
			ImGui::Text(tmpSpriteList->GetName().c_str());
			if (ImGui::CollapsingHeader("Transform"))
			{
				// ��������u���Ƃ�
				float tmpPos[3] =
				{
					tmpSpriteList->GetComponent<Transform>("Transform")->pos.x,
					tmpSpriteList->GetComponent<Transform>("Transform")->pos.y,
					tmpSpriteList->GetComponent<Transform>("Transform")->pos.z,
				};
				float tmpRot[3] =
				{
					tmpSpriteList->GetComponent<Transform>("Transform")->rot.x,
					tmpSpriteList->GetComponent<Transform>("Transform")->rot.y,
					tmpSpriteList->GetComponent<Transform>("Transform")->rot.z,
				};
				float tmpScale[3] =
				{
					tmpSpriteList->GetComponent<Transform>("Transform")->scale.x,
					tmpSpriteList->GetComponent<Transform>("Transform")->scale.y,
					tmpSpriteList->GetComponent<Transform>("Transform")->scale.z,
				};

				//ImGui::Text("	x		  y		  z");
				ImGui::DragFloat3("Postion", tmpPos, 1);
				ImGui::DragFloat3("Rotation", tmpRot, 0.2);
				ImGui::DragFloat3("Scale", tmpScale, 0.01);

				tmpSpriteList->GetComponent<Transform>("Transform")->pos.x = tmpPos[0];
				tmpSpriteList->GetComponent<Transform>("Transform")->pos.y = tmpPos[1];
				tmpSpriteList->GetComponent<Transform>("Transform")->pos.z = tmpPos[2];

				tmpSpriteList->GetComponent<Transform>("Transform")->rot.x = tmpRot[0];
				tmpSpriteList->GetComponent<Transform>("Transform")->rot.y = tmpRot[1];
				tmpSpriteList->GetComponent<Transform>("Transform")->rot.z = tmpRot[2];

				tmpSpriteList->GetComponent<Transform>("Transform")->scale.x = tmpScale[0];
				tmpSpriteList->GetComponent<Transform>("Transform")->scale.y = tmpScale[1];
				tmpSpriteList->GetComponent<Transform>("Transform")->scale.z = tmpScale[2];
			}
			if (ImGui::CollapsingHeader("Texture"))
			{
				vector <string> tmpTags = gameTextureList->GetAllTextureTag();
				const char* tags[2056]{};
				for (int i = 0; i < 2056; i++)
				{
					if (tags[i] == NULL) tags[i] = " ";
				}
				for (int i = 0; i < tmpTags.size(); i++)
				{
					tags[i] = tmpTags[i].c_str();
				}
				static int tagCurrent = -1;
				static int item_current_idx = 0;
				for (int i = 0; i < 2056; i++)
				{
					if (tmpSpriteList->GetComponent<Texture>("Texture")->GetTextureTag() == tags[i])
						tagCurrent = i;
				}

				if (ImGui::Combo("Texture Tag Name", &tagCurrent, tags, 2056))
				{
					tmpSpriteList->SetTexture(*gameTextureList->GetTexture((tags[tagCurrent])));
				}
			}
			break;
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
