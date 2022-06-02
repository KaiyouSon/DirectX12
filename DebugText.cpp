#include "DebugText.h"
#include "DebugManager.h"

void DebugText::Initialize()
{
	for (int i = 0; i < maxCharCount; i++)
	{
		sprites[i].Initialize(Square::view2D, Vec2(9, 18));
	}
}

void DebugText::Printf(float x, float y, const Vec4& color, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	int w = vsnprintf(buffer, maxCharCount - 1, fmt, args);
	TmpPrintString(x, y, color, buffer);
	va_end(args);
}

void DebugText::DrawAll(const Texture& texture)
{
	if (DebugManager::GetInstance()->GetisDebug() == true)
	{
		// 全ての文字のスプライトに
		for (int i = 0; i < spriteIndex; i++)
		{
			// スプライトの描画
			sprites[i].SetTexture(texture);
			sprites[i].Draw();
		}

		spriteIndex = 0;
	}
}

void DebugText::TmpPrintString(float x, float y, const Vec4& color, const std::string& text)
{
	// 全ての文字について
	for (int i = 0; i < text.size(); i++)
	{
		// 最大文字数超過
		if (spriteIndex >= maxCharCount) break;

		// 1文字取り出す(※ASCIIコードでしか成り立たない)
		const unsigned char& character = text[i];

		// ASCIIコードの2段分飛ばした番号を計算
		int fontIndex = character - 32;
		if (character >= 0x7f) fontIndex = 0;

		int fontIndexY = fontIndex / fontLineCount;
		int fontIndexX = fontIndex % fontLineCount;

		// 座標計算
		transform.pos = { (x + fontWidth * 1 * i) + 4.5f, y + 9, 0 };
		transform.scale = { 1,1,1 };
		transform.rot = { 0,0,0 };
		sprites[spriteIndex].Update(transform);

		sprites[spriteIndex].SetCutPosAndSize(
			Vec2(fontIndexX * (float)fontWidth, fontIndexY * (float)fontHeight),
			Vec2(fontWidth, fontHeight));

		sprites[spriteIndex].SetColor(color);

		// 文字を1つ進める
		spriteIndex++;
	}
}

DebugText* DebugText::GetInstance()
{
	static DebugText* debugText = new DebugText;
	return debugText;
}

void DebugText::DestroyInstance()
{
	delete GetInstance();
}


