#pragma once
#include "Square.h"
#include "MathUtil.h"
#include "Transform.h"
#include <string>

class DebugText
{
private:
	static const int maxCharCount = 256;
	static const int fontWidth = 9;
	static const int fontHeight = 18;
	static const int fontLineCount = 14;

	Square sprites[256];
	int spriteIndex = 0;

	Transform transform;

	// 書式付き文字列展開用バッファ
	char buffer[maxCharCount] = {};

private:
	void TmpPrintString(float x, float y, const Vec4& color, const std::string& text);

public:
	void Initialize(const Texture& texture);
	void Printf(float x, float y, const Vec4& color, const char* fmt, ...);

	void DrawAll();

	static DebugText* GetInstance();
	static void DestroyInstance();
private:
	DebugText() = default;
	~DebugText() = default;

	DebugText(const DebugText&) = delete;
	DebugText& operator=(const DebugText&) = delete;
	DebugText(const DebugText&&) = delete;
	DebugText& operator=(const DebugText&&) = delete;
};