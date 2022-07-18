#pragma once
#include <string>

void NewEngineInit();
void NewEngineUpda();
void NewEnginePreDraw();
void NewEneineDraw();
void NewEnginePostDraw();
void NewEngineEnd();

// ウインドウ関連
bool ProcessMessage();
void SetWindowSize(int WIN_WIDTH, int WIN_HEIGHT);
void SetWindowTitle(const std::string TITLE);
void SetBackgroundColor(float Red, float Green, float Blue);
