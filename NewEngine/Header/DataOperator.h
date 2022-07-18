#pragma once
#include "NewEngine/Header/Developer/Math/MathUtil.h"
#include <string>
class DataOperator
{
private:
	std::string gameWindowTitleForStorage;
	Vec2 gameWindowSizeForStorage;

public:
	void Initialize();

	void SaveData();
	void LoadData();

	// �Q�[���E�B���h�E�f�[�^
	void SaveWindowData();
	void LoadWindowData();

	// ���f���f�[�^���X�g
	void SaveModelDataList();
	void LoadModelDataList();

	// �e�N�X�`���[���X�g
	void SaveTextureList();
	void LoadTextureList();

	// �Q�[���I�u�W�F�N�g���X�g
	void SaveGameObjectList();
	void LoadGameObjectList();

	bool CheckSaveData();
	void SetGameWindowParameter(std::string title, Vec2 size);

	std::string GetGameWindowTitleForStorage();
	Vec2 GetGameWindowSizeForStorage();

	static DataOperator* GetInstance();
	static void DestroyInstance();
private:
	DataOperator() = default;
	~DataOperator() = default;

	DataOperator(const DataOperator&) = delete;
	DataOperator& operator=(const DataOperator&) = delete;
	DataOperator(const DataOperator&&) = delete;
	DataOperator& operator=(const DataOperator&&) = delete;
};

