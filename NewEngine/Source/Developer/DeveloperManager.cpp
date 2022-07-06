#include "NewEngine/Header/Developer/DeveloperManager.h"
#include "NewEngine/Header/Developer/Input/InputManager.h"
#include "NewEngine/Header/Developer/Debug/DebugManager.h"
#include "NewEngine/Header/Developer/Object/Other/ObjectManager.h"
#include "NewEngine/Header/Developer/Object/Other/ViewProjection.h"
#include "NewEngine/Header/Developer/Sound.h"

void DeveloperManager::Initialize()
{
	InputManager::GetInstance()->Initialize();
#ifdef _DEBUG
	DebugManager::GetInstance()->Initialize();
#endif
	SoundManager::GetInstance()->Initialize();
	ViewProjection::GetInstance()->Initialize();
	Random::Initialize();
}
void DeveloperManager::Update()
{
	InputManager::GetInstance()->Update();
#ifdef _DEBUG
	DebugManager::GetInstance()->Update();
#endif
	ObjectManager::GetInstance()->Update();
}

void DeveloperManager::Draw3D()
{
	ObjectManager::GetInstance()->Draw3D();
}
void DeveloperManager::Draw2DToBack()
{
	ObjectManager::GetInstance()->Draw2DToBack();
}
void DeveloperManager::Draw2DToForward()
{
#ifdef _DEBUG
	DebugManager::GetInstance()->Draw();
#endif
	ObjectManager::GetInstance()->Draw2DToForward();
}

DeveloperManager* DeveloperManager::GetInstance()
{
	static DeveloperManager* developerManager = new DeveloperManager;
	return developerManager;
}
void DeveloperManager::DestroyInstance()
{
	InputManager::DestoryInstance();
#ifdef _DEBUG
	DebugManager::DestroyInstance();
#endif
	SoundManager::DestroyInstance();
	ObjectManager::DestroyInstance();
	ViewProjection::DestroyInstance();
	delete GetInstance();
}
