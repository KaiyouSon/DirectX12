#pragma once
#include <dinput.h>
#include <wrl.h>
class KeyBoardInput
{
private:
	Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard;
	BYTE keys[256] = { 0 };
	BYTE oldkeys[256] = { 0 };
public:
	void Initialize();	// 初期化
	void Update();		// 更新処理

	// キーの取得関連
	bool GetKey(BYTE key);
	bool GetKeyTrigger(BYTE key);
	bool GetKeyReleased(BYTE key);

	static KeyBoardInput& GetInstance();
private:
	KeyBoardInput() = default;
	~KeyBoardInput() = default;

	KeyBoardInput(const KeyBoardInput&) = delete;
	KeyBoardInput& operator=(const KeyBoardInput&) = delete;
	KeyBoardInput(const KeyBoardInput&&) = delete;
	KeyBoardInput& operator=(const KeyBoardInput&&) = delete;
};