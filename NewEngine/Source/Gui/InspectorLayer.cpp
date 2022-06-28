#include "NewEngine/Header/Gui/InspectorLayer.h"
#include "NewEngine/Header/Gui/GuiManager.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "NewEngine/Header/Developer/Object/Other/ObjectManager.h"

void InspectorLayer::Initialize()
{
	size = { 480,WIN_HEIGHT };
	pos = { WIN_WIDTH - size.x,0 };
}

void InspectorLayer::Update()
{
	ImGuiWindowFlags window_flags = 0;
	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
	ImGui::Begin("Inspector", nullptr, window_flags |= ImGuiWindowFlags_NoCollapse);

	//std::vector<Object3D*> tmpObjectList = ObjectManager::GetInstance()->GetObjectList();
	//for (int i = 0; i < ObjectManager::GetInstance()->GetObjectList().size(); i++)
	//{
	//	// 選択したオブジェクトのコンポネントをInspectorウィンドウに表示
	//	if (tmpObjectList[i]->GetisShowDataToInspector())
	//	{
	//		ImGui::Text(tmpObjectList[i]->GetTag().c_str());
	//		if (ImGui::CollapsingHeader("Transform"))
	//		{
	//			// いったん置いとく
	//			float tmpPos[3] =
	//			{
	//				tmpObjectList[i]->GetComponent<Transform>("Transform")->pos.x,
	//				tmpObjectList[i]->GetComponent<Transform>("Transform")->pos.y,
	//				tmpObjectList[i]->GetComponent<Transform>("Transform")->pos.z,
	//			};
	//			float tmpRot[3] =
	//			{
	//				tmpObjectList[i]->GetComponent<Transform>("Transform")->rot.x,
	//				tmpObjectList[i]->GetComponent<Transform>("Transform")->rot.y,
	//				tmpObjectList[i]->GetComponent<Transform>("Transform")->rot.z,
	//			};
	//			float tmpScale[3] =
	//			{
	//				tmpObjectList[i]->GetComponent<Transform>("Transform")->scale.x,
	//				tmpObjectList[i]->GetComponent<Transform>("Transform")->scale.y,
	//				tmpObjectList[i]->GetComponent<Transform>("Transform")->scale.z,
	//			};

	//			ImGui::DragFloat3("Postion", tmpPos, 0.05);
	//			ImGui::DragFloat3("Rotation", tmpRot, 0.1);
	//			ImGui::DragFloat3("Scale", tmpScale, 0.01);

	//			tmpObjectList[i]->GetComponent<Transform>("Transform")->pos.x = tmpPos[0];
	//			tmpObjectList[i]->GetComponent<Transform>("Transform")->pos.y = tmpPos[1];
	//			tmpObjectList[i]->GetComponent<Transform>("Transform")->pos.z = tmpPos[2];

	//			tmpObjectList[i]->GetComponent<Transform>("Transform")->rot.x = tmpRot[0];
	//			tmpObjectList[i]->GetComponent<Transform>("Transform")->rot.y = tmpRot[1];
	//			tmpObjectList[i]->GetComponent<Transform>("Transform")->rot.z = tmpRot[2];

	//			tmpObjectList[i]->GetComponent<Transform>("Transform")->scale.x = tmpScale[0];
	//			tmpObjectList[i]->GetComponent<Transform>("Transform")->scale.y = tmpScale[1];
	//			tmpObjectList[i]->GetComponent<Transform>("Transform")->scale.z = tmpScale[2];
	//		}
	//	}
	//}

	for (auto tmpObjectList : ObjectManager::GetInstance()->GetObjectList())
	{
		// 選択したオブジェクトのコンポネントをInspectorウィンドウに表示
		if (tmpObjectList->GetisShowDataToInspector())
		{
			ImGui::Text(tmpObjectList->GetTag().c_str());
			if (ImGui::CollapsingHeader("Transform"))
			{
				// いったん置いとく
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
			break;
		}
	}

	ImGui::End();
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
