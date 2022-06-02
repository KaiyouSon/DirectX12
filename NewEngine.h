#pragma once
#include <string>
void NewEngineInit();
void NewEngineEnd();
void ProcessMessage();

// ウインドウ関連
void SetWindowSize(int WIN_WIDTH, int WIN_HEIGHT);
void SetWindowTitle(const std::string TITLE);
bool CloseWindow();
void SetBackgroundColor(float Red, float Green, float Blue);
void NewEnginePreDraw();
void NewEngineSetDraw3D();
void NewEngineSetDraw2D();
void NewEnginePostDraw();