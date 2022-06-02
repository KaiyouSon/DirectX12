#pragma once
#include "TextureBuffer.h"
class DebugManager
{
private:
	bool isDebug;
	Texture debugTexture;

public:
	void Initialize();
	void Update();
	void Draw();

	static DebugManager* GetInstance();
	static void DestroyInstance();
	bool GetisDebug();
private:
	DebugManager() = default;
	~DebugManager() = default;

	DebugManager(const DebugManager&) = delete;
	DebugManager& operator=(const DebugManager&) = delete;
	DebugManager(const DebugManager&&) = delete;
	DebugManager& operator=(const DebugManager&&) = delete;
};

