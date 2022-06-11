#include "DebugManager.h"
#include "DebugText.h"
#include "TextureBuffer.h"
#include "InputManager.h"

DebugText* debugtext = DebugText::GetInstance();

void DebugManager::Initialize()
{
	debugTexture = TextureBuffer::LoadTexture("Resources/debugfont.png");

	// �f�o�b�O�e�L�X�g�̏�����
	DebugText::GetInstance()->Initialize();
}

void DebugManager::Update()
{
	if (key->GetKeyTrigger(DIK_F5))
	{
		if (isDebug == true) isDebug = false;
		else				 isDebug = true;
	}
}

void DebugManager::Draw()
{
	DebugText::GetInstance()->DrawAll(debugTexture);
}

DebugManager* DebugManager::GetInstance()
{
	static DebugManager* debugManager = new DebugManager;
	return debugManager;
}

void DebugManager::DestroyInstance()
{
	// �f�o�b�O�e�L�X�g�̔j��
	DebugText::GetInstance()->DestroyInstance();

	delete GetInstance();
}

bool DebugManager::GetisDebug()
{
	return isDebug;
}