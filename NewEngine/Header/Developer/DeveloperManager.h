#pragma once
class DeveloperManager
{
public:
	void Initialize();
	void Update();
	void Draw3D();
	void Draw2DToBack();
	void Draw2DToForward();

	static DeveloperManager* GetInstance();
	static void DestroyInstance();
private:
	DeveloperManager() = default;
	~DeveloperManager() = default;

	DeveloperManager(const DeveloperManager&) = delete;
	DeveloperManager& operator=(const DeveloperManager&) = delete;
	DeveloperManager(const DeveloperManager&&) = delete;
	DeveloperManager& operator=(const DeveloperManager&&) = delete;
};