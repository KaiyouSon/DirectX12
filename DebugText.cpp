#include "DebugText.h"

void DebugText::Initialize(const Texture& texture)
{
	for (int i = 0; i < maxCharCount; i++)
	{
		sprites[i].SetTexture(texture);
		sprites[i].Initialize(Square::view2D, Vec2(9, 18));
	}
}

void DebugText::Printf(const Vec2& pos, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	int w = vsnprintf(buffer, maxCharCount - 1, fmt, args);
	TmpPrintString(pos.x, pos.y, buffer);
	va_end(args);
}

void DebugText::Printf(float x, float y, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	int w = vsnprintf(buffer, maxCharCount - 1, fmt, args);
	TmpPrintString(x, y, buffer);
	va_end(args);
}

void DebugText::DrawAll()
{
	// �S�Ă̕����̃X�v���C�g��
	for (int i = 0; i < spriteIndex; i++)
	{
		// �X�v���C�g�̕`��
		sprites[i].Draw();
	}

	spriteIndex = 0;
}

void DebugText::TmpPrintString(float x, float y, const std::string& text)
{
	// �S�Ă̕����ɂ���
	for (int i = 0; i < text.size(); i++)
	{
		// �ő啶��������
		if (spriteIndex >= maxCharCount) break;

		// 1�������o��(��ASCII�R�[�h�ł������藧���Ȃ�)
		const unsigned char& character = text[i];

		// ASCII�R�[�h��2�i����΂����ԍ����v�Z
		int fontIndex = character - 32;
		if (character >= 0x7f) fontIndex = 0;

		int fontIndexY = fontIndex / fontLineCount;
		int fontIndexX = fontIndex % fontLineCount;

		// ���W�v�Z
		transform.pos = { (x + fontWidth * 1 * i) + 4.5f, y + 9, 0 };
		transform.scale = { 1,1,1 };
		transform.rot = { 0,0,0 };
		sprites[spriteIndex].Update(transform);

		sprites[spriteIndex].SetCutPosAndSize(
			Vec2(fontIndexX * (float)fontWidth, fontIndexY * (float)fontHeight),
			Vec2(fontWidth, fontHeight));

		// ������1�i�߂�
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


