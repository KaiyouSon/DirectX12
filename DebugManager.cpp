#include "DebugManager.h"
#include "DebugText.h"
#include "TextureBuffer.h"
#include "Input.h"

void DebugManager::Initialize()
{
	// デバッグテキストの初期化
	DebugText::GetInstance()->Initialize(
		Texture::LoadTexture(L"Resources/debugfont.png"));
}

void DebugManager::Update()
{
	if (Input::Key().GetKeyTrigger(DIK_F5))
	{
		if (isDebug == true) isDebug = false;
		else				 isDebug = true;
	}
}

void DebugManager::Draw()
{
	DebugText::GetInstance()->DrawAll();
}

DebugManager* DebugManager::GetInstance()
{
	static DebugManager* debugManager = new DebugManager;
	return debugManager;
}

void DebugManager::DestroyInstance()
{
	// デバッグテキストの破棄
	DebugText::GetInstance()->DestroyInstance();

	delete GetInstance();
}

bool DebugManager::GetisDebug()
{
	return isDebug;
}
