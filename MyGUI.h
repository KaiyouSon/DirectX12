#pragma once
class MyGUI
{
public:
	void Initialize();
	void Update();
	void Draw();

	static MyGUI* GetInstance();
	static void DestroyInstance();
private:
	MyGUI() = default;
	~MyGUI() = default;

	MyGUI(const MyGUI&) = delete;
	MyGUI& operator=(const MyGUI&) = delete;
	MyGUI(const MyGUI&&) = delete;
	MyGUI& operator=(const MyGUI&&) = delete;
}typedef GUI;