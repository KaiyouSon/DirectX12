#pragma once

#define DIRECTINPUT_VERSION 0x0800	// DirectInputのバージョン指定
#include <dinput.h>

class Input
{
private:
	IDirectInput8* directInput = nullptr;
	IDirectInputDevice8* keyboard = nullptr;

	BYTE keys[256] = { 0 };
	BYTE oldkeys[256] = { 0 };

public:
	void Initialize();	// 初期化
	void Update();		// 更新処理

	/// <summary>
	/// キーが押されてる時
	/// </summary>
	/// <param name="keys">キー番号( DIK_0 等)</param>
	/// <returns>キーが押されてる時</returns>
	bool GetKey(BYTE key);

	/// <summary>
	/// キーを押した瞬間
	/// </summary>
	/// <param name="keys">キー番号( DIK_0 等)</param>
	/// <returns>キーを押した瞬間</returns>
	bool GetKeyTrigger(BYTE key);

	/// <summary>
	/// キーを離した瞬間
	/// </summary>
	/// <param name="keys">キー番号( DIK_0 等)</param>
	/// <returns>キーを離した瞬間</returns>
	bool GetKeyReleased(BYTE key);

	static Input& GetInstance();

private:
	Input() = default;
	~Input() = default;

	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;
	Input(const Input&&) = delete;
	Input& operator=(const Input&&) = delete;

};