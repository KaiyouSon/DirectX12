#pragma once
class GuiManager
{
public:
	void Initialize();
	void Update();
	void Draw();

	static GuiManager* GetInstance();
	static void DestroyInstance();
private:
	GuiManager() = default;
	~GuiManager();

	GuiManager(const GuiManager&) = delete;
	GuiManager& operator=(const GuiManager&) = delete;
	GuiManager(const GuiManager&&) = delete;
	GuiManager& operator=(const GuiManager&&) = delete;
}typedef GuiManager;

